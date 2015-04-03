// This is the main DLL file.

#include "stdafx.h"
#include "Devices.h"

#define DllExport __declspec(dllexport)

using namespace System;
using namespace System::IO::Ports;

extern "C"
{
	DllExport bool Connect()
	{
		Devices::arduino = gcnew SerialPort("COM3", 9600);

		try
		{
			Devices::arduino->Open();
			return true;
		}
		catch (IO::IOException^ e)
		{

		}
		catch (ArgumentException^ e)
		{

		}

		return false;
	}


	bool IsCanOperate()
	{
		bool isCanOperate = false;

		if (Devices::arduino != nullptr && Devices::arduino->IsOpen)
		{
			isCanOperate = true;
		}

		return isCanOperate;
	}

	DllExport bool Write(int singnal)
	{
		if (Devices::arduino != nullptr)
		{
			if (!Devices::arduino->IsOpen)
			{
				Devices::arduino->Open();
			}

			try
			{

				if (singnal == 0)
				{
					Devices::arduino->WriteLine("0"); // send 0 to arduino 
				}
				else if (singnal == 1)
				{
					Devices::arduino->WriteLine("1"); // send 1 to arduino
				}
				else
				{

				}


				return true;
			}
			catch (IO::IOException^ e)
			{
			}
			catch (ArgumentException^ e)
			{
			}

		}

		return false;
	}

	DllExport bool Write(int signal, int data)
	{
		bool bIsWriteSuccessful = true;

		if (IsCanOperate())
		{
			try
			{
				Devices::arduino->WriteLine(signal+"_"+data);
				return true;
			}
			catch (IO::IOException^ e)
			{
				bIsWriteSuccessful = false;
			}
			catch (ArgumentException^ e)
			{
				bIsWriteSuccessful = false;
			}
		}

		return bIsWriteSuccessful;
	}

	DllExport char[] Write()
	{
		char text[];

		return text;
	}


	DllExport bool WriteLine(String^ singnal)
	{
		bool bIsWriteSuccessful = true;

		if (IsCanOperate())
		{
			try
			{
				Devices::arduino->WriteLine(singnal); // send 0 to arduino 
				return true;
			}
			catch (IO::IOException^ e)
			{
				bIsWriteSuccessful = false;
			}
			catch (ArgumentException^ e)
			{
				bIsWriteSuccessful = false;
			}
		}

		return bIsWriteSuccessful;
	}




	DllExport int Read()
	{
		if (Devices::arduino != nullptr)
		{
			if (!Devices::arduino->IsOpen)
			{
				Devices::arduino->Open();
			}

			try
			{
				Devices::arduino->ReadLine();
			}
			catch (IO::IOException^ e)
			{
			}
			catch (ArgumentException^ e)
			{
			}

		}

		return 0;
	}


	DllExport String^ ReadLine()
	{
		String^ readContent = "<Empty>" ;

		if (IsCanOperate())
		{
			try
			{
				readContent = Devices::arduino->ReadLine();
			}
			catch (IO::IOException^ e)
			{

			}
			catch (ArgumentException^ e)
			{

			}
		}

		return readContent;
	}


	DllExport void Disconnect()
	{
		if (IsCanOperate())
		{
			Devices::arduino->Close();
		}
	}


	/*
	DllExport bool WriteByteArray(unsigned char val[])
	{
		bool bIsWriteSuccessful = true;

		if (IsCanOperate())
		{
			try
			{
				array<unsigned char>^ test = gcnew array<unsigned char>(10){ 1, 2, 3 };

				//Devices::arduino->Write(val, 0, 1);
				Devices::arduino->Write(test, 0, 0);
				
			}
			catch (IO::IOException^ e)
			{
				bIsWriteSuccessful = false;
			}
			catch (ArgumentException^ e)
			{
				bIsWriteSuccessful = false;
			}

		}

		return bIsWriteSuccessful;
	}

	
	DllExport bool WriteByte(Byte val)
	{
	return WriteByteArray(new Byte[1] {val});
	}

	DllExport bool WriteInt16(Int16 val)
	{
		return true;
	}

	DllExport bool WriteInt16Array(Int16 val[])
	{
		return true;
	}

	DllExport bool WriteInt32(Int32 val)
	{
		return true;
	}

	DllExport bool WriteInt32Array(Int32 val[])
	{
		return true;
	}

	DllExport bool WriteFloat(float val)
	{
		return true;
	}

	DllExport bool WriteFloatArray(float val[])
	{
		return true;
	}

	DllExport bool WriteString(char val[])
	{
		return true;
	}*/
}