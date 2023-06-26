%{
/*
Tokai Embedded Processor 16  (TEP16)
lburg spec.
*/

enum { REG1=1, REG2=2, REG3=3, REG4=4, REG5=5, REG6=6, REG7=7, REG8=8, REG9=9, REG10=10, REG11=11, REG12=12, REG13=13, REG14=14 };
#include "c.h"
#define NODEPTR_TYPE Node
#define OP_LABEL(p) ((p)->op)
#define LEFT_CHILD(p) ((p)->kids[0])
#define RIGHT_CHILD(p) ((p)->kids[1])
#define STATE_LABEL(p) ((p)->x.state)
extern int ckstack(Node, int);
extern int memop(Node);
extern int sametree(Node, Node);
static Symbol intreg[32];
static Symbol intregw;
static int cseg;
extern char *stabprefix;
extern void stabblock(int, int, Symbol*);
extern void stabend(Coordinate *, Symbol, Coordinate **, Symbol *, Symbol *);
extern void stabfend(Symbol, int);
extern void stabinit(char *, int, char *[]);
extern void stabline(Coordinate *);
extern void stabsym(Symbol);
extern void stabtype(Symbol);
static int local_frame;

#define hasargs(p) (p->syms[0] && p->syms[0]->u.c.v.i > 0 ? 0 : LBURG_MAX)
%}
%start stmt
%term CNSTI1=1045
%term CNSTI2=2069
%term CNSTP2=2071
%term CNSTU1=1046
%term CNSTU2=2070
%term ARGB=41
%term ARGI2=2085
%term ARGP2=2087
%term ARGU2=2086
%term ASGNB=57
%term ASGNI1=1077
%term ASGNI2=2101
%term ASGNP2=2103
%term ASGNU1=1078
%term ASGNU2=2102
%term INDIRB=73
%term INDIRI1=1093
%term INDIRI2=2117
%term INDIRP2=2119
%term INDIRU1=1094
%term INDIRU2=2118
%term CVFI2=2165
%term CVII1=1157
%term CVII2=2181
%term CVIU1=1158
%term CVIU2=2182
%term CVPU2=2198
%term CVUI1=1205
%term CVUI2=2229
%term CVUP2=2231
%term CVUU1=1206
%term CVUU2=2230
%term NEGI2=2245
%term CALLB=217
%term CALLI2=2261
%term CALLP2=2263
%term CALLU2=2262
%term CALLV=216
%term RETI2=2293
%term RETP2=2295
%term RETU2=2294
%term RETV=248
%term ADDRGP2=2311
%term ADDRFP2=2327
%term ADDRLP2=2343
%term ADDI2=2357
%term ADDP2=2359
%term ADDU2=2358
%term SUBI2=2373
%term SUBP2=2375
%term SUBU2=2374
%term LSHI2=2389
%term LSHU2=2390
%term MODI2=2405
%term MODU2=2406
%term RSHI2=2421
%term RSHU2=2422
%term BANDI2=2437
%term BANDU2=2438
%term BCOMI2=2453
%term BCOMU2=2454
%term BORI2=2469
%term BORU2=2470
%term BXORI2=2485
%term BXORU2=2486
%term DIVI2=2501
%term DIVU2=2502
%term MULI2=2517
%term MULU2=2518
%term EQI2=2533
%term EQU2=2534
%term GEI2=2549
%term GEU2=2550
%term GTI2=2565
%term GTU2=2566
%term LEI2=2581
%term LEU2=2582
%term LTI2=2597
%term LTU2=2598
%term NEI2=2613
%term NEU2=2614
%term JUMPV=584
%term LABELV=600
%term LOADI1=1253
%term LOADU1=1254
%term LOADI2=2277
%term LOADU2=2278
%term VREGP=711

%%

stmt:	ASGNI1(VREGP,reg)	"# write register\n"		
stmt:	ASGNU1(VREGP,reg)	"# write register\n"		
stmt:	ASGNI2(VREGP,reg)	"# write register\n"		
stmt:	ASGNU2(VREGP,reg)	"# write register\n"		
stmt:	ASGNP2(VREGP,reg)	"# write register\n"		
stmt:	reg	""		
stmt:	ASGNI1(addr,reg)	"ST1 %1,%0\n"	1	
stmt:	ASGNI2(addr,reg)	"ST2 %1,%0\n"	1	
stmt:	ASGNU1(addr,reg)	"ST1 %1,%0\n"	1	
stmt:	ASGNU2(addr,reg)	"ST2 %1,%0\n"	1	
stmt:	ASGNP2(addr,reg)	"ST2 %1,%0\n"	1	
stmt:	ARGI2(reg)	"# ARG\n"	1	
stmt:	ARGU2(reg)	"# ARG\n"	1	
stmt:	LABELV	"%a:\n"		
stmt:	JUMPV(addr)	"JUMP %0\n"	3	
stmt:	EQI2(reg,reg)  	"JEQ %0,%1,%a\n"		
stmt:	GEI2(reg,reg)	"JGEI %0,%1,%a\n"		
stmt:	GTI2(reg,reg)	"JGTI %0,%1,%a\n"		
stmt:	LEI2(reg,reg)	"JLEI %0,%1,%a\n"		
stmt:	LTI2(reg,reg)	"JLTI %0,%1,%a\n"		
stmt:	NEI2(reg,reg)	"JNE %0,%1,%a\n"		
stmt:	GEU2(reg,reg)	"JGEU %0,%1,%a\n"		
stmt:	GTU2(reg,reg)	"JGTU %0,%1,%a\n"		
stmt:	LEU2(reg,reg)	"JLEU %0,%1,%a\n"		
stmt:	LTU2(reg,reg)	"JLTU %0,%1,%a\n"		
stmt:	EQU2(reg,reg)	"JEQ %0,%1,%a\n"		
stmt:	NEU2(reg,reg)	"JNE %0,%1,%a\n"		
stmt:	CALLV(addr)	"#CALL WITH ARGS\n"	hasargs(a)	
stmt:	CALLV(addr)	"CALL $2,%0\n"	1	
stmt:	RETI2(reg)	"# RET\n"		
stmt:	RETU2(reg)	"# RET\n"		
stmt:	RETP2(reg)	"# RET\n"		

reg:	cnst	"CNST %c,$0,%0\n"		
reg:	INDIRI1(VREGP)	"# read register\n"		
reg:	INDIRU1(VREGP)	"# read register\n"		
reg:	INDIRI2(VREGP)	"# read register\n"		
reg:	INDIRP2(VREGP)	"# read register\n"		
reg:	INDIRU2(VREGP)	"# read register\n"		
reg:	LOADI1(reg)	"LSHL %c,%0,0\n"	move(a)	
reg:	LOADI2(reg)	"LSHL %c,%0,0\n"	move(a)	
reg:	LOADU1(reg)	"LSHL %c,%0,0\n"	move(a)	
reg:	LOADU2(reg)	"LSHL %c,%0,0\n"	move(a)	
reg:	ADDI2(reg,reg)	"?LSHL %c,%0,0\nADD %c,%1\n"	1	
reg:	ADDP2(reg,reg)  "?LSHL %c,%0,0\nADD %c,%1\n"	1	
reg:	ADDU2(reg,reg)	"?LSHL %c,%0,0\nADD %c,%1\n"	1	
reg:	SUBI2(reg,reg)	"?LSHL %c,%0,0\nSUB %c,%1\n"	1	
reg:	SUBP2(reg,reg)	"?LSHL %c,%0,0\nSUB %c,%1\n"	1	
reg:	SUBU2(reg,reg)	"?LSHL %c,%0,0\nSUB %c,%1\n"	1	
reg:	MULI2(reg,reg)	"?LSHL %c,%0,0\nMUL %c,%1\n"	1	
reg:	MULU2(reg,reg)	"?LSHL %c,%0,0\nMUL %c,%1\n"	1	
reg:	DIVI2(reg,reg)	"CALL $2,$0,DIVI2\n"	1	
reg:	DIVU2(reg,reg)	"CALL $2,$0,DIVU2\n"	1	
reg:	MODI2(reg,reg)	"CALL $2,$0,MODI2\n"	1	
reg:	MODU2(reg,reg)	"CALL $2,$0,MODU2\n"	1	
reg:	BANDI2(reg,reg)	"?LSHL %c,%0,0\nBAND %c,%1\n"	1	
reg:	BORI2(reg,reg)	"?LSHL %c,%0,0\nBOR %c,%1\n"	1	
reg:	BXORI2(reg,reg)	"?LSHL %c,%0,0\nBXOR %c,%1\n"	1	
reg:	BANDU2(reg,reg)	"?LSHL %c,%0,0\nBAND %c,%1\n"	1	
reg:	BORU2(reg,reg)	"?LSHL %c,%0,0\nBOR %c,%1\n"	1	
reg:	BXORU2(reg,reg)	"?LSHL %c,%0,0\nBXOR %c,%1\n"	1	
reg:	BCOMI2(reg)        	"BCOM %c,%0\n"	2	
reg:	BCOMU2(reg)        	"BCOM %c,%0\n"	2	
reg:	NEGI2(reg)         	"NEGI2 %c,%0\n"	2	
reg:	LSHI2(reg,cnst4)     	"LSHL %c,%0,%1  ;lshi\n"	2	
reg:	LSHU2(reg,cnst4)     	"LSHL %c,%0,%1  ;lshu\n"	2	
reg:	RSHI2(reg,cnst4)	"RSHA %c,%0,%1\n"	2	
reg:	RSHU2(reg,cnst4)	"RSHL %c,%0,%1\n"	2	
reg:	CVPU2(reg)	"?LSHL %c,%0,0\n"  	move(a)	
reg:	CVUP2(reg)	"?LSHL %c,%0,0\n"  	move(a)	
reg:	CVII2(reg)	"# extend\n"	3	
reg:	CVIU2(reg)	"# extend\n"	3	
reg:	CVUI2(reg)	"# extend\n"	3	
reg:	CVUU2(reg)	"?LSHL %c,%0,0\n"  	3	
reg:	CVII1(reg) 	"# truncate\n"	1	
reg:	CVII2(reg) 	"# truncate\n"	1	
reg:	CVUU1(reg)	"?LSHL %c,%0,0\n"  	1	
reg:	CVUU2(reg)	"?LSHL %c,%0,0\n"  	1	
reg:	CALLI2(addr)  	"#CALL WITH ARGS\n"	hasargs(a)	
reg:	CALLU2(addr)  	"#CALL WITH ARGS\n"	hasargs(a)	
reg:	CALLP2(addr)	"#CALL WITH ARGS\n"	hasargs(a)	
reg:	CALLI2(addr)	"CALL $2,%0\n"	1	
reg:	CALLU2(addr)	"CALL $2,%0\n"	1	
reg:	CALLP2(addr)	"CALL $2,%0\n"	1	
reg:	INDIRI1(addr)	"LD1 %c,%0      ;indiri\n"		
reg:	INDIRU1(addr)	"LD1 %c,%0      ;indiru\n"		
reg:	INDIRI2(addr)	"LD2 %c,%0      ;indiri\n"		
reg:	INDIRU2(addr)	"LD2 %c,%0      ;indiru\n"		
reg:	INDIRP2(addr)	"LD2 %c,%0      ;indirp\n"		
reg:	addr		"CNST %c,%0\n"

addr:	reg	"%0,0"	
addr:	acon	"$0,%0"	
addr:	ADDI2(reg,acon)	"%0,%1"	
addr:	ADDU2(reg,acon)	"%0,%1"	
addr:	ADDP2(reg,acon)	"%0,%1"	
addr:	ADDRFP2	"$15,%a+%F"	
addr:	ADDRLP2	"$15,%a+%F"	
addr:	ADDRGP2	"$0,%a"	

cnst:	CNSTI1	"%a"	
cnst:	CNSTU1	"%a"	
cnst:	CNSTI2	"%a"	
cnst:	CNSTU2	"%a"	
cnst:	CNSTP2	"%a"	
cnst4:	CNSTI1	"%a"	range(a,0,15)
cnst4:	CNSTU1	"%a"	range(a,0,15)
cnst4:	CNSTI2	"%a"	range(a,0,15)
cnst4:	CNSTU2	"%a"	range(a,0,15)
cnst4:	CNSTP2	"%a"	range(a,0,15)
acon:	cnst	"%0"	
acon:	ADDRGP2	"%a"	

%%
static void progbeg(int argc, char *argv[]) {
        int i;
/*
        extern Interface tepIR;

#define xx(f) assert(!tepIR.f); tepIR.f = tepIR.f
        xx(address);
        xx(local);
        xx(x.blkfetch);
        xx(x.blkstore);
        xx(x.blkloop);
        xx(x.doarg);
#undef xx
*/

        intreg[REG1]   = mkreg("$1", REG1, 1, IREG);
        intreg[REG2]   = mkreg("$2", REG2, 1, IREG);
        intreg[REG3]   = mkreg("$3", REG3, 1, IREG);
        intreg[REG4]   = mkreg("$4", REG4, 1, IREG);
        intreg[REG5]   = mkreg("$5", REG5, 1, IREG);
        intreg[REG6]   = mkreg("$6", REG6, 1, IREG);
        intreg[REG7]   = mkreg("$7", REG7, 1, IREG);
        intreg[REG8]   = mkreg("$8", REG8, 1, IREG);
        intreg[REG9]   = mkreg("$9", REG9, 1, IREG);
        intreg[REG10]   = mkreg("$10", REG10, 1, IREG);
        intreg[REG11]   = mkreg("$11", REG11, 1, IREG);
        intreg[REG12]   = mkreg("$12", REG12, 1, IREG);
        intreg[REG13]   = mkreg("$13", REG13, 1, IREG);
        intreg[REG14]   = mkreg("$14", REG14, 1, IREG);
        intregw = mkwildcard(intreg);

        tmask[IREG] = 0x7FFE;
	/*
	( (1<<REG1)|(1<<REG2)|(1<<REG3)|(1<<REG4)|
	(1<<REG5)|(1<<REG6)|(1<<REG7)|(1<<REG8)|
	(1<<REG9)|(1<<REG10)|(1<<REG11)|(1<<REG12)|
	(1<<REG13)|(1<<REG14)) ;
	*/
        vmask[IREG] = 0;
        cseg = 0;
        stabprefix = ".LL";
}

static Symbol rmap(int opk) {
        switch (optype(opk)) {
		        case B: case P: case I: case U: case F:
		        	if (( opsize(opk) == 1) || ( opsize(opk) == 2 ) )
		                return intregw;
		        default:
		                return 0;
		        }
}

static Symbol prevg;

static void globalend(void) {
        if (prevg && prevg->type->size > 0)
                print(".size %s,%d\n", prevg->x.name, prevg->type->size);
        prevg = NULL;
}

static void progend(void) {
        globalend();
        (*IR->segment)(CODE);
        print(".ident \"LCC: 4.2 for TEP\"\n");
}

static void target(Node p) {
        assert(p);
        
        switch (specific(p->op)) {
        case DIV+I: case DIV+U: case MOD+I: case MOD+U:
        				rtarget(p, 0, intreg[REG3]);
        				rtarget(p, 1, intreg[REG4]);
        				break;

        case CALL+I: case CALL+U: case CALL+P: case CALL+V:
								setreg(p, intreg[REG1]);
                break;
        case RET+I: case RET+U: case RET+P:
                rtarget(p, 0, intreg[REG1]);
                break;
        }
        
}

static void clobber(Node p) {
        static int nstack = 0;
        assert(p);
        nstack = ckstack(p, nstack);
        switch (specific(p->op)) {
        case DIV+I: case DIV+U: case MOD+I: case MOD+U:
                spill(1<<REG1 | 1<<REG2 | 1<<REG13 | 1<<REG14, IREG, p);
                break;
        case CALL+I: case CALL+U: case CALL+P: case CALL+V:
                spill(
		1<<REG2|
		1<<REG3|1<<REG4|
		1<<REG5|1<<REG6|
		1<<REG7|1<<REG8|
		1<<REG9|1<<REG10|
		1<<REG11|1<<REG12|
		1<<REG13|1<<REG14
		, IREG, p);
                break;
				
        }
}

static void emit2(Node p) {
        int op = specific(p->op);
#define preg(f) ((f)[getregnum(p->x.kids[0])]->x.name)

        if 			(op == CVI+I && opsize(p->op) == 2 && opsize(p->x.kids[0]->op) == 1)
                print("CVI2 %s,%s\n", p->syms[RX]->x.name, preg(intreg));
        else if (op == CVI+U && opsize(p->op) == 2 && opsize(p->x.kids[0]->op) == 1)
                print("CVI2 %s,%s\n", p->syms[RX]->x.name, preg(intreg));
        else if (generic(op) == CVI || generic(op) == CVU) {
        				char *dst = intreg[getregnum(p)]->x.name;
                char *src = preg(intreg);
                if (dst != src)
                        print("LSHL %s,%s,0\n", dst, src);
        }else if(generic(op) == ARG){
                print("CNST $15,$15,-2\t;ARG\nST2 %s,$15,0\n",preg(intreg));
                framesize += 2;
        }else if(generic(op) == CALL){
                if((p->kids[0]->syms[0]) == NULL){
                        print("CALL $2,%s,0\t;INDIR_CALL\nCNST $15,$15,%d\n",p->kids[0]->syms[2]->x.name,framesize - local_frame);       
                }else{
                        print("CALL $2,$0,%s\t;CALL\nCNST $15,$15,%d\n",p->kids[0]->syms[0]->x.name,framesize - local_frame);
                }
                framesize = local_frame;
        }
}

static void function(Symbol f, Symbol caller[], Symbol callee[], int n) {
        int i;

        globalend();
        print(".align 2\n");
        print(".type %s,@function\n", f->x.name);
        print("%s:\n", f->x.name);        
        print("CNST $15,$15,-2\n");
        print("ST2 $2,$15,0\n");
        usedmask[0] = usedmask[1] = 0;
        freemask[0] = freemask[1] = ~0U;
        offset = 2;
        for (i = 0; callee[i]; i++) {
                Symbol p = callee[i];
                Symbol q = caller[i];
                assert(q);
                offset = roundup(offset, q->type->align);
                p->x.offset = q->x.offset = offset;
                p->x.name = q->x.name = stringf("%d", p->x.offset);
                p->sclass = q->sclass = AUTO;
                offset += roundup(q->type->size, 2);
        }
        assert(caller[i] == 0);
        offset = maxoffset = 0;
        gencode(caller, callee);
        framesize = local_frame = roundup(maxoffset, 2);
        if (framesize > 0)
                print("CNST $15,$15,-%d\n", framesize);
        print("; ------------------------------\n");
        emitcode();
        print("; ------------------------------\n");
        
        print("LD2 $2,$15,%d\n",framesize);
        print("CNST $15,$15,%d\n",framesize+2);
        print("JUMP $2,0\n");
        { int l = genlabel(1);
          print(".Lf%d:\n", l);
          print(".size %s,.Lf%d-%s\n", f->x.name, l, f->x.name);
        }
}

static void defsymbol(Symbol p) {
        if (p->scope >= LOCAL && p->sclass == STATIC)
                p->x.name = stringf("%s.%d", p->name, genlabel(1));
        else if (p->generated)
                p->x.name = stringf(".LC%s", p->name);
        else if (p->scope == GLOBAL || p->sclass == EXTERN)
                p->x.name = stringf("%s", p->name);
        else
                p->x.name = p->name;
}

static void segment(int n) {
        if (n == cseg)
                return;
        cseg = n;
        if (cseg == CODE)
                print(".text\n");
        else if (cseg == BSS)
                print(".bss\n");
        else if (cseg == DATA || cseg == LIT)
                print(".data\n");
}

static void defconst(int suffix, int size, Value v) {
        if (suffix == I && size == 1)
                print(".byte %d\n", (int)v.u);
        else if (suffix == I && size == 2)
                print(".word %d\n", (int)v.i);
        else if (suffix == I && size == 4)
                print(".long %d\n", (int)v.i);
        else if (suffix == U && size == 1)
                print(".byte %d\n", (int)((char)v.u));
        else if (suffix == U && size == 2)
                print(".word %d\n", (int)v.u);
        else if (suffix == P && size == 2)
                print(".word %d\n", (int)v.p);
        else if (suffix == U && size == 4)
                print(".long %d\n", (int)v.u);
        else if (suffix == P && size == 4)
                print(".long %d\n", (int)v.p);
        else if (suffix == F && size == 4) {
                float f = v.d;
                print(".long %d\n", (int)(*(unsigned *)&f));
        } else if (suffix == F && size == 8) {
                double d = v.d;
                unsigned *p = (unsigned *)&d;
                print(".long %d\n.long %d\n", (int)p[swap], (int)p[!swap]);
        }
        else assert(0);
}

static void defaddress(Symbol p) {
        print(".long %s\n", p->x.name);
}

static void defstring(int n, char *str) {
        char *s;

        for (s = str; s < str + n; s++)
                print(".byte %d\n", (*s)&0377);
}

static void export(Symbol p) {
        globalend();
        print(".globl %s\n", p->x.name);
}

static void import(Symbol p) {}

static void global(Symbol p) {
        globalend();
        print(".align %d\n", p->type->align > 2 ? 2 : p->type->align);
        if (!p->generated) {
                print(".type %s,@%s\n", p->x.name,
                        isfunc(p->type) ? "function" : "object");
                if (p->type->size > 0)
                        print(".size %s,%d\n", p->x.name, p->type->size);
                else
                        prevg = p;
        }
        if (p->u.seg == BSS) {
                if (p->sclass == STATIC)
                        print(".lcomm %s,%d\n", p->x.name, p->type->size);
                else
                        print(".comm %s,%d\n", p->x.name, p->type->size);
        } else {
                print("%s:\n", p->x.name);
        }
}

static void space(int n) {
        if (cseg != BSS)
                print(".space %d\n", n);
}
static void doarg(Node p) {
        assert(p && p->syms[0]);
        mkactual(2, p->syms[0]->u.c.v.i);
}
static void blkfetch(int k, int off, int reg, int tmp) {}
static void blkstore(int k, int off, int reg, int tmp) {}
static void blkloop(int dreg, int doff, int sreg, int soff,
        int size, int tmps[]) {}
static void local(Symbol p) {
        if (isfloat(p->type))
                p->sclass = AUTO;
        if (askregvar(p, (*IR->x.rmap)(ttob(p->type))) == 0) {
                assert(p->sclass == AUTO);
                offset = roundup(offset + p->type->size,
                        p->type->align < 2 ? 2 : p->type->align);
                p->x.offset = -offset;
                p->x.name = stringd(-offset);
        }
}
static void address(Symbol q, Symbol p, long n) {
        if (p->scope == GLOBAL
        || p->sclass == STATIC || p->sclass == EXTERN)
                q->x.name = stringf("%s%s%D",
                        p->x.name, n >= 0 ? "+" : "", n);
        else {
                assert(n <= INT_MAX && n >= INT_MIN);
                q->x.offset = p->x.offset + n;
                q->x.name = stringd(q->x.offset);
        }
}
Interface tepIR = {
        1, 1, 0,  /* char */
        2, 2, 0,  /* short */
        2, 2, 0,  /* int */
        2, 2, 0,  /* long */
        2, 2, 0,  /* long long */
        4, 4, 1,  /* float */
        8, 4, 1,  /* double */
        8, 4, 1,  /* long double */
        2, 2, 0,  /* T * */
        0, 1, 0,  /* struct */
        1,        /* little_endian */
        0,        /* mulops_calls */
        1,        /* wants_callb */
        1,        /* wants_argb */
        0,        /* left_to_right */
        0,        /* wants_dag */
        0,        /* unsigned_char */
        address, /* address */
        blockbeg,
        blockend,
        defaddress,
        defconst,
        defstring,
        defsymbol,
        emit,
        export,
        function,
        gen,
        global,
        import,
        local, /* local */
        progbeg,
        progend,
        segment,
        space,
	0,0,0,0,0,0,0,
//        stabblock, stabend, 0, stabinit, stabline, stabsym, stabtype,
        {1, rmap,
            blkfetch, blkstore, blkloop,    /* blkfetch, blkstore, blkloop */
            _label,
            _rule,
            _nts,
            _kids,
            _string,
            _templates,
            _isinstruction,
            _ntname,
            emit2,
            doarg, /* doarg */
            target,
            clobber,
        }
};
