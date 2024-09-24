// CPPWebService.h

#pragma once
#using "System.EnterpriseServices.dll"

namespace CPPWebService
{
	__value public struct ClientData
	{
		String *Name;
		int	ID;
	};

	__gc public class ClientInfo
	{
		String *Name;
		int	ID;
	};

	typedef ClientData ClientArray[];

	__gc class MyService 
	{
	public:
		[WebMethod] 
		int MyMethod();

		[WebMethod]
		ClientData GetClientData();

		[WebMethod]
		ClientArray GetClientsData(int Number);
	};
}