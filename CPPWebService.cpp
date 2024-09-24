// Written by Chris Maunder (chris@codeproject.com)
// The Code Project, http://www.codeproject.com

#include "stdafx.h"
#using <mscorlib.dll>
#using "System.Web.dll"
#using "System.Web.Services.dll"

using namespace System;
using namespace System::Web;
using namespace System::Web::Services;

#include "CPPWebService.h"

namespace CPPWebService
{
	int MyService::MyMethod()
	{
		return 42;
	}

	ClientData MyService::GetClientData()
	{
		ClientData data;
		data.Name = new String("Client Name");
		data.ID = 1;

		return data;
	}

	ClientArray MyService::GetClientsData(int Number)
	{
		// simple sanity checks
		if (Number < 0 || Number > 10)
			return 0;

		ClientArray data = new ClientData __gc[Number];

		if (Number > 0 && Number <= 10)
		{
			for (int i = 0; i < Number; i++)
			{
				data[i].Name = new String("Client ");
				data[i].Name->Concat(i.ToString());
				data[i].ID = i;
			}
		}

		return data;
	}
};
