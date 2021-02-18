/*****************************************************
	project: DIES HW Field object implementation
	version: 1.0
	author:	 gyenist

******************************************************/

#include <stdio.h>
#pragma once

char* fieldInput;
char* fieldOutput;
int fieldClkReset;
int fieldClkSync;
enum state { reset, connecting, connected };
enum state fieldState;

static inline void setFieldState(enum state val) {
	fieldState = val;
}

static inline void setFieldInput(char* str) {
	fieldInput = str;
}

static inline void setFieldOutput(char* str) {
	fieldOutput = str;
}
static inline void setFieldClkReset(int val) {
	fieldClkReset = val;
}

static inline void resetFieldClkReset() {
	fieldClkReset = 0;
}

static inline void setFieldClkSync(int val) {
	fieldClkSync = val;
}

static inline void resetFieldClkSync() {
	fieldClkSync = 0;
}


static inline void fieldObject(fieldState) {
	int tRTMax = 2;
	int tSync = 2;
	switch (fieldState)
	{
	case reset:
		if (fieldInput == "OBJ2" || fieldInput == "OBJDOWN")
		{
			setFieldState(reset);
			break;
		}

		if (fieldClkSync >= tSync)
		{
			setFieldOutput("OBJ1");
			resetFieldClkReset();
			resetFieldClkSync();
			setFieldState(connecting);
			printf("%s", "connecting!\n");
			break;
		}
		break;

	case connecting:
		if (fieldClkReset >= tRTMax)
		{
			setFieldState(reset);
			break;
		}
		else if (fieldInput == "OBJ2")
		{
			setFieldOutput("OBJ1");
			resetFieldClkSync();
			setFieldState(connected);
			printf("%s", "connected!\n");
			break;
		}
		else if (fieldInput == "OBJDOWN")
		{
			setFieldState(connecting);
			break;
		}
		else if (fieldClkSync >= tSync)
		{
			setFieldState(connecting);
			setFieldOutput("OBJ1");
			resetFieldClkSync();
			break;
		}
		break;

	case connected:
		if (fieldClkReset >= tRTMax)
		{
			setFieldState(reset);
			break;
		}
		else if (fieldClkSync >= tSync)
		{
			setFieldOutput("OBJUP");
			resetFieldClkSync();
			break;
		}
		else if (fieldInput == "OBJ2")
		{
			setFieldState(connected);
			break;
		}
		else if (fieldInput == "OBJDOWN")
		{
			setFieldState(connected);
			resetFieldClkReset();
			break;
		}
		break;

	default:
		printf("%s", "Unknown state of the Field object.\n");
		break;
	}
}