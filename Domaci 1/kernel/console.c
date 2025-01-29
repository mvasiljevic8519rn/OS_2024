// Console input and output.
// Input is from the keyboard or serial port.
// Output is written to the screen and serial port.

#include "types.h"
#include "defs.h"
#include "param.h"
#include "traps.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"

static void consputc(int);

static int panicked = 0;

static struct {
	struct spinlock lock;
	int locking;
} cons;

static void
printint(int xx, int base, int sign)
{
	static char digits[] = "0123456789abcdef";
	char buf[16];
	int i;
	uint x;

	if(sign && (sign = xx < 0))
		x = -xx;
	else
		x = xx;

	i = 0;
	do{
		buf[i++] = digits[x % base];
	}while((x /= base) != 0);

	if(sign)
		buf[i++] = '-';

	while(--i >= 0)
		consputc(buf[i]);
}

// Print to the console. only understands %d, %x, %p, %s.
void
cprintf(char *fmt, ...)
{
	int i, c, locking;
	uint *argp;
	char *s;

	locking = cons.locking;
	if(locking)
		acquire(&cons.lock);

	if (fmt == 0)
		panic("null fmt");

	argp = (uint*)(void*)(&fmt + 1);
	for(i = 0; (c = fmt[i] & 0xff) != 0; i++){
		if(c != '%'){
			consputc(c);
			continue;
		}
		c = fmt[++i] & 0xff;
		if(c == 0)
			break;
		switch(c){
		case 'd':
			printint(*argp++, 10, 1);
			break;
		case 'x':
		case 'p':
			printint(*argp++, 16, 0);
			break;
		case 's':
			if((s = (char*)*argp++) == 0)
				s = "(null)";
			for(; *s; s++)
				consputc(*s);
			break;
		case '%':
			consputc('%');
			break;
		default:
			// Print unknown % sequence to draw attention.
			consputc('%');
			consputc(c);
			break;
		}
	}

	if(locking)
		release(&cons.lock);
}

void
panic(char *s)
{
	int i;
	uint pcs[10];

	cli();
	cons.locking = 0;
	// use lapiccpunum so that we can call panic from mycpu()
	cprintf("lapicid %d: panic: ", lapicid());
	cprintf(s);
	cprintf("\n");
	getcallerpcs(&s, pcs);
	for(i=0; i<10; i++)
		cprintf(" %p", pcs[i]);
	panicked = 1; // freeze other CPU
	for(;;)
		;
}

#define BACKSPACE 0x100
#define CRTPORT 0x3d4
static ushort *crt = (ushort*)P2V(0xb8000);  // CGA memory

static int curentLinePos;
static int pos;

static void
cgaputc(int c)
{

	// Cursor position: col + 80*row.
	outb(CRTPORT, 14);
	pos = inb(CRTPORT+1) << 8;
	outb(CRTPORT, 15);
	pos |= inb(CRTPORT+1);


	if(c == '\n'){
		pos += 80 - pos%80;
		curentLinePos=pos+2;
	}
	else if(c == BACKSPACE){
		if(pos > 0) --pos;
	} else{
		crt[pos++] = (c&0xff) | 0x0700;  // black on white
		// crt[curentLinePos++]= ('a'&0xff) | 0xff00;

	}
	if(pos < 0 || pos > 25*80)
		panic("pos under/overflow");

	if((pos/80) >= 24){  // Scroll up.
		memmove(crt, crt+80, sizeof(crt[0])*23*80);
		pos -= 80;
		curentLinePos=pos+2;
		memset(crt+pos, 0, sizeof(crt[0])*(24*80 - pos));
	}

	outb(CRTPORT, 14);
	outb(CRTPORT+1, pos>>8);
	outb(CRTPORT, 15);
	outb(CRTPORT+1, pos);
	// crt[curentLinePos]= ('a'&0xff) | 0xff00;
	crt[pos] = ' ' | 0x0700;
}

void
consputc(int c)
{
	if(panicked){
		cli();
		for(;;)
			;
	}

	if(c == BACKSPACE){
		uartputc('\b'); uartputc(' '); uartputc('\b');
	} else
		uartputc(c);
	cgaputc(c);
}
#define C(x)  ((x)-'@')  // Control-x
#define HISTORY_BUF 128
#define INPUT_BUF 128
struct {
	char buf[INPUT_BUF];
	uint r;  // Read index
	uint w;  // Write index
	uint e;  // Edit index
} input;

static int duzinaIstorije=0;
static int trenutni=2;
static int insertPos=0;
static int history1[HISTORY_BUF];

static int history1Br=0;

static int historyList[3][HISTORY_BUF];
static int historyListBr[3];


static int historyListBuffer[HISTORY_BUF];
static int BufferBr=0;

// memset(history1,0,sizeof(history1));

void
writeHistory(){
	if(trenutni<duzinaIstorije){
		// curentWritenLenght=0;
		int curentWritenLenght=input.e-input.w;
		for(int i=0 ;i < curentWritenLenght+1 ; i++){
			crt[curentLinePos+i] = ' ' | 0x0200;
		}
		input.e=input.w;
		
		for(int i=0 ; i < history1Br ;i ++){
			input.buf[input.e++ % INPUT_BUF] = history1[i];
			crt[curentLinePos+i] = history1[i] | 0x0200;

		}
	int pomPos=curentLinePos+history1Br;
	outb(CRTPORT, 14);
	outb(CRTPORT+1, pomPos>>8);
	outb(CRTPORT, 15);
	outb(CRTPORT+1, pomPos);
	}
	trenutni++;
}

static int histroyFlag=0;
void
writeHistoryList(){

	if(duzinaIstorije > trenutni){
		// curentWritenLenght=0;


		int curentWritenLenght=input.e-input.w;
		
		for(int i=0;i<HISTORY_BUF;i++){
			historyListBuffer[i]=0;
		}
		BufferBr=0;

		for(int i=0 ;i < curentWritenLenght+1 ; i++){
			crt[curentLinePos+i] = ' ' | 0x0200;
		}
		input.e=input.w;
		
		for(int i=0 ; i < historyListBr[trenutni] ;i ++){
			input.buf[input.e++ % INPUT_BUF] = historyList[trenutni][i];
			historyListBuffer[i] = historyList[trenutni][i];
			crt[curentLinePos+i] = historyList[trenutni][i] | 0x0200;
		}
	
	BufferBr=historyListBr[trenutni] ;
	int pomPos=curentLinePos+historyListBr[trenutni];
	outb(CRTPORT, 14);
	outb(CRTPORT+1, pomPos>>8);
	outb(CRTPORT, 15);
	outb(CRTPORT+1, pomPos);
	
	}

}
static int deletePom=0;
static int downToUp=0;
void
consoleintr(int (*getc)(void))
{
	int c, doprocdump = 0;

	acquire(&cons.lock);
	while((c = getc()) >= 0){
		switch(c){

		case 1:{
			if(downToUp==1){
				trenutni--;
				downToUp=0;
			}
			histroyFlag=1;
			writeHistoryList();
				if(trenutni>0)
				trenutni--;
		}break;	
		case 2:{
			if(histroyFlag==1)
			if( trenutni==1 || trenutni==2 || trenutni==0 ){	
			downToUp=1;
			
			if(duzinaIstorije==3){
				deletePom=0;
			}
			if(duzinaIstorije==2){
				deletePom=1;
			}
				trenutni++;
			if(trenutni==3-deletePom || duzinaIstorije==1){
				histroyFlag=0;
				downToUp=0;
				int pomPos=curentLinePos+historyListBr[trenutni];
				outb(CRTPORT, 14);
				outb(CRTPORT+1, pomPos>>8);
				outb(CRTPORT, 15);
				outb(CRTPORT+1, pomPos);
				
				if(duzinaIstorije==1)
				trenutni=0;
				else if(duzinaIstorije==2)
				trenutni=1;
				else if(duzinaIstorije==3)
				trenutni=2;
				int curentWritenLenght=input.e-input.w;
		
				for(int i=0;i<HISTORY_BUF;i++){
					historyListBuffer[i]=0;
				}
				BufferBr=0;

				for(int i=0 ;i < curentWritenLenght+1 ; i++){
					crt[curentLinePos+i] = ' ' | 0x0200;
				}
				input.e=input.w;

			
				break;
			}
			writeHistoryList();
			}
		}break;		
		case C('P'):  // Process listing.
			// procdump() locks cons.lock indirectly; invoke later
			doprocdump = 1;
			break;
		case C('U'):  // Kill line.
			while(input.e != input.w &&
			      input.buf[(input.e-1) % INPUT_BUF] != '\n'){
				input.e--;
				consputc(BACKSPACE);
			}
			break;
		case C('H'): case '\x7f':  // Backspace
			if(input.e != input.w){
				input.e--;
			
				if(history1Br!=0)
				history1Br--;

				if(historyListBr[insertPos]!=0){
					historyListBr[insertPos]--;
				}
				//buffer basckspace
				if(BufferBr!=0){
					BufferBr--;
				}

				consputc(BACKSPACE);
			}
			break;
		default:
			if(c != 0 && input.e-input.r < INPUT_BUF){
				c = (c == '\r') ? '\n' : c;
				input.buf[input.e++ % INPUT_BUF] = c;

				if(duzinaIstorije==0){ history1[history1Br++]=c;}
				
				// historyList[insertPos][historyListBr[insertPos]++]=c;
				
				historyListBuffer[BufferBr++]=c;

				consputc(c);
				if(c == '\n' || c == C('D') || input.e == input.r+INPUT_BUF){
					input.w = input.e;
				
					if(duzinaIstorije==3 && BufferBr!=0){
						//setting 0 in history to 0
						for(int i=0;i<HISTORY_BUF;i++){
							historyList[0][i]=0;
						}
						historyListBr[0]=0;

						//setting 0 in history to 1
						for(int i=0;i<historyListBr[1];i++){
							historyList[0][i]=historyList[1][i];
						}
						historyListBr[0]=historyListBr[1];

						//setting 1 in history to 0
						for(int i=0;i<HISTORY_BUF;i++){
							historyList[1][i]=0;
						}
						historyListBr[1]=0;

						//setting 1 in history to 2
						for(int i=0;i<historyListBr[2];i++){
							historyList[1][i]=historyList[2][i];
						}
						historyListBr[1]=historyListBr[2];

						//setting 2 in history to 0
						for(int i=0;i<HISTORY_BUF;i++){
							historyList[2][i]=0;
						}
						historyListBr[2]=0;
						
						BufferBr--;
						for(int i=0;i<BufferBr;i++){
							historyList[2][i]=historyListBuffer[i];
						}
						historyListBr[2]=BufferBr;

						//cisti se buffer
						for(int i=0;i<HISTORY_BUF;i++){
							historyListBuffer[i]=0;
						}

						insertPos++;
						BufferBr=0;
						
						trenutni=2;
						if(trenutni>duzinaIstorije){
						trenutni=duzinaIstorije;
						}
					}
					// if(history1Br!=0 && duzinaIstorije==0)
					// history1Br--;
					
					// if(history1Br!=0 && duzinaIstorije<3)
					// duzinaIstorije++;
					
					// if(history1Br!=0 && duzinaIstorije==0)
					// history1Br--;
					
					//buffer logic
					else if(BufferBr!=0){
						BufferBr--;
					 	for(int i=0;i<BufferBr;i++){
							 historyList[insertPos][i]=historyListBuffer[i];
						}
						historyListBr[insertPos]=BufferBr;
						
						for(int i=0;i<HISTORY_BUF;i++){
							historyListBuffer[i]=0;
						}

						insertPos++;
						
						trenutni=2;
						if(trenutni>duzinaIstorije){
						trenutni=duzinaIstorije;
						}


					 }
					 
						if(BufferBr!=0 && duzinaIstorije<3)
						{
						duzinaIstorije++;
						BufferBr=0;
						}
					//  if(BufferBr!=0 && duzinaIstorije<3)

					// if(BufferBr!=0 && duzinaIstorije<3)
					// 	duzinaIstorije++;

					// if(historyListBr[insertPos]!=0)
					// 	historyListBr[insertPos]--;
					// if(historyListBr[insertPos]!=0 && duzinaIstorije<3){
					// 	duzinaIstorije++;
					// }
    				
					// memset(historyListBuffer, 0, sizeof(historyListBuffer)); 

					wakeup(&input.r);
				}
			}
			break;
		}
	}
	release(&cons.lock);
	if(doprocdump) {
		procdump();  // now call procdump() wo. cons.lock held
	}
}

int
consoleread(struct inode *ip, char *dst, int n)
{
	uint target;
	int c;

	iunlock(ip);
	target = n;
	acquire(&cons.lock);
	while(n > 0){
		while(input.r == input.w){
			if(myproc()->killed){
				release(&cons.lock);
				ilock(ip);
				return -1;
			}
			sleep(&input.r, &cons.lock);
		}
		c = input.buf[input.r++ % INPUT_BUF];
		if(c == C('D')){  // EOF
			if(n < target){
				// Save ^D for next time, to make sure
				// caller gets a 0-byte result.
				input.r--;
			}
			break;
		}
		*dst++ = c;
		--n;
		if(c == '\n')
			break;
	}
	release(&cons.lock);
	ilock(ip);

	return target - n;
}

int
consolewrite(struct inode *ip, char *buf, int n)
{
	int i;

	iunlock(ip);
	acquire(&cons.lock);
	for(i = 0; i < n; i++)
		consputc(buf[i] & 0xff);
	release(&cons.lock);
	ilock(ip);

	return n;
}

void
consoleinit(void)
{
	initlock(&cons.lock, "console");

	devsw[CONSOLE].write = consolewrite;
	devsw[CONSOLE].read = consoleread;
	cons.locking = 1;

	ioapicenable(IRQ_KBD, 0);
}
