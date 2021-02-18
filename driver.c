/*****************************************************
	project: DIES HW coverage test driver implementation
	version: 1.0
	author:	 gyenist

******************************************************/


#include <stdio.h>
#include "field.c"

void main()
{
	for (int b = 0; b <= 10; b++)
	{
		setFieldState(reset);
		setFieldInput("NA");
		resetFieldClkReset();
		resetFieldClkSync();

		if (b == 0)
		{
			setFieldState(5);
		}
		else if (b == 1)
		{
			setFieldInput("OBJ2");
		}
		else if (b == 2)
		{
			setFieldClkSync(3);
		}
		else if (b == 3)
		{
			setFieldClkSync(3);
			fieldObject(fieldState);
			setFieldClkReset(3);
		}
		else if (b == 4)
		{
			setFieldClkSync(3);
			fieldObject(fieldState);
			setFieldInput("OBJ2");
		}
		else if (b == 5)
		{
			setFieldClkSync(3);
			fieldObject(fieldState);
			setFieldInput("OBJDOWN");
		}
		else if (b == 6)
		{
			setFieldClkSync(3);
			fieldObject(fieldState);
			setFieldClkSync(3);
		}
		else if (b == 7)
		{
			setFieldClkSync(3);
			fieldObject(fieldState);
			setFieldInput("OBJ2");
			fieldObject(fieldState);
			setFieldClkReset(3);
		}
		else if (b == 8)
		{
			setFieldClkSync(3);
			fieldObject(fieldState);
			setFieldInput("OBJ2");
			fieldObject(fieldState);
			setFieldClkSync(3);
		}
		else if (b == 9)
		{
			setFieldClkSync(3);
			fieldObject(fieldState);
			setFieldInput("OBJ2");
			fieldObject(fieldState);
			setFieldInput("OBJ2");
		}
		else if (b == 10)
		{
			setFieldClkSync(3);
			fieldObject(fieldState);
			setFieldInput("OBJ2");
			fieldObject(fieldState);
			setFieldInput("OBJDOWN");
		}


		fieldObject(fieldState);
		printf("%s\n", fieldOutput);
	}
}