/*****************************************************
	project: DIES HW environment implementation
	version: 1.0
	author:	 gyenist

******************************************************/

#include <stdio.h>
#include "field.c"
#pragma warning(disable : 4996)

//CONTROL OBJECT:
char* controlInput;
char* controlOutput;
int controlClkReset;
int controlClkSync;
enum state controlState;

void setControlState(enum state val) {
	controlState = val;
}

void setControlInput(char* str) {
	controlInput = str;
}

void setControlOutput(char* str) {
	controlOutput = str;
}
void setControlClkReset(int val) {
	controlClkReset = val;
}

void resetControlClkReset() {
	controlClkReset = 0;
}

void setControlClkSync(int val) {
	controlClkSync = val;
}

void resetControlClkSync() {
	controlClkSync = 0;
}


void controlObject(controlState) {
	int tRTMax = 2;
	int tSync = 2;
	switch (controlState)
	{
	case reset:
		if (controlInput == "OBJUP")
		{
			setControlState(reset);
			break;
		}

		if (controlInput == "OBJ1")
		{
			setControlOutput("OBJ2");
			resetControlClkReset();
			setControlState(connecting);
			break;
		}
		break;

	case connecting:
		if (controlClkReset >= tRTMax)
		{
			setControlState(reset);
			break;
		}
		else if (controlInput == "NA" || controlInput == "OBJ1")
		{
			setControlState(connecting);
			break;
		}
		else if (controlInput == "OBJUP")
		{
			setControlOutput("OBJDOWN");
			resetControlClkSync();
			setControlState(connected);
			break;
		}
		break;

	case connected:
		if (controlClkReset >= tRTMax)
		{
			setControlState(reset);
			break;
		}
		else if (controlInput == "NA" || controlInput == "OBJ1")
		{
			setControlState(connected);
			break;
		}
		else if (controlInput == "OBJUP")
		{
			setControlOutput("OBJDOWN");
			resetControlClkReset();
			break;
		}
		break;

	default:
		printf("%s", "Unknown state of the control object.\n");
	}
}

//SCHEDULER
void main()
{
	FILE* fp = fopen("messagelog.txt", "w");

	//init
	setFieldState(reset);
	setControlState(reset);
	setFieldInput("NA");
	setControlInput("NA");
	resetFieldClkReset();
	resetControlClkReset();

	//handshake
	setFieldClkSync(3);
	fieldObject(fieldState);
	printf("%s\n", fieldOutput);
	fprintf(fp, "%s\n", fieldOutput);
	setControlInput(fieldOutput); //send OBJ1 to control input
	controlObject(controlState);
	setFieldInput(controlOutput); //send OBJ2 to field input
	printf("%s\n",fieldInput);
	fprintf(fp, "%s\n", fieldInput);
	fieldObject(fieldState);
	setFieldClkSync(3);
	fieldObject(fieldState);

	//communication
	for (int i = 0; i <= 3; i++)
	{
		printf("%s\n" ,fieldOutput);
		fprintf(fp, "%s\n", fieldOutput);
		setControlInput(fieldOutput); //send OBJUP to control input
		controlObject(controlState);
		setFieldInput(controlOutput); //send OBJDOWN to field input
		printf("%s\n", fieldInput);
		fprintf(fp, "%s\n", fieldInput);
	}
	fclose(fp);
}