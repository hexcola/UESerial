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

	DllExport bool WriteData(int signal, int data)
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

	/*
	// TO-DO : implement read data from arduino
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
	*/

	DllExport void Disconnect()
	{
		if (IsCanOperate())
		{
			Devices::arduino->Close();
		}
	}
}