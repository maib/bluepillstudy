#include <stdio.h>
//#include <stdlib.h>
#include <windows.h>
//#include <dos.h>
#include <conio.h>

#define SNPROTECTOR_VERIFY	1000 //Used to tell the hypervisor to start run the target program
#define SNPROTECTOR_HIDEDRV 	2000 //Used to hide the hypervisor code in the kernel space
#define SNPROTECTOR_UNHIDEDRV 	2500 //Used to reveal the hypervisor code in the kernel space

typedef struct _Parameter
{
	CHAR UserName[4];
	CHAR SerialNumber[4];
} Parameter,*PParameter;

BOOLEAN bRegState; //Store the software registration state in the software side.

void RegSuccessful()
{
	printf("Thank you for your registration!\n");
}

void RegFailure()
{
	printf("Wrong SN\n");
}

/**
 * Pass <pParameter> Argument to Context Counter
 * Return: The virtual address of result struct.
 * The content of the structure <pParameter> points to will be copied to the kernel memory.
 * <actionType>:either to be START_RECORD or END_RECORD or PING
 */
//BOOLEAN __stdcall VerifySN (PParameter pParameter) {
//	__asm { 
//		mov eax, SNPROTECTOR_VERIFY
//		mov edx, pParameter
//		cpuid
//	}
//	return;
//}
BOOLEAN __stdcall VerifySN (ULONG UserName,ULONG SN) {
	__asm { 
		mov eax, SNPROTECTOR_VERIFY
		mov ebx, UserName
		mov ecx, SN
		//mov edx, pParameter
		cpuid
	}
	return;
}

VOID __stdcall HideHypervisor(){
	__asm{
		mov eax,SNPROTECTOR_HIDEDRV
		cpuid
	}
}
VOID __stdcall RevealHypervisor(){
	__asm{
		mov eax,SNPROTECTOR_UNHIDEDRV
		cpuid
	}
}

int __cdecl main(int argc, char **argv) {
	Parameter passin;
	CHAR ch[10];
	if (argc != 3 && argc !=1) {
		printf ("Crackme <UserName> <S/N Key>\n");
		printf ("Crackme\n Reveal the hypervisor in the kernel space\n");
		return 0;
	}
	else if(argc == 1)
	{
		RevealHypervisor();
		return 0;
	}
	
	//Waiting for loading the Protector.
	scanf("%s",ch);
	printf ("Load the SNProtector\n");

	//Construct Parameter struct
	memcpy(passin.UserName,argv[1],4);
	memcpy(passin.SerialNumber,argv[2],4);
	
	__try {
		HideHypervisor();
		bRegState = VerifySN((ULONG)(*((PULONG)passin.UserName)),(ULONG)(*((PULONG)passin.SerialNumber))); 
	} __except (EXCEPTION_EXECUTE_HANDLER) {
		printf ("CPUDID caused exception");
		return 0;
	}
	
	//I am Cracker!!!
	//bRegState = TRUE;

	//Output proper information in the client side.
	if(bRegState)
	{
		RegSuccessful();
	}
	else
	{
		RegFailure();
	}
	
	//To simulate a real commercial software
	while(bRegState)
	{
		printf("Work Work!\n");
		Sleep(2000);
	}
	//we won't permit it exit.
	while(1){Sleep(2000);}
	return 0;
}
