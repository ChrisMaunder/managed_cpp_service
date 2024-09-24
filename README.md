# Your first managed C++ Web Service

An introduction to writing your first WebService using C++ with managed extensions

<!-- Article Starts -->



## Introduction

This article assumes you are familiar with [declaring and 
using managed types](/managedcpp/managed_types.asp) and the [.NET Garbage Collector](/managedcpp/garbage_collection.asp).

Creating your first web service is incredibly easy if you use C# or VB.NET (see my 
[previous article](/webservices/myservice.asp) for details). Writing a WebService
using managed C++ in .NET is also extremely simple, but there are a couple of 'gotcha's that
can cause a few frustrating moments. 

My first suggestion is to use the Visual Studio .NET Wizards to create your WebService (in fact it's
a great idea for all your apps when you are first starting out). This is especially
important if you are moving up through the various builds of the beta bits of .NET. What is perfectly
acceptable in one build may fail to compile in another build, and it may be difficult to work out
which piece of the puzzle you are missing.

Using the Wizards can get you a managed C++ WebService up and running in minutes, but things 
can start to get a little weird as soon as you try something a little more risqué.

For this example I have created a service called `MyCPPService` by using the Wizard. Simply
select File | New Project and run through the wizard to create a C++ WebService.

A new namespace will be defined called `CPPWebService`, and within this namespace will be the 
classes and structures that implement your webservice. For this example I have called the class
`MyService`. Other files that are created by the wizard include the  *.asmx* file that
acts as a proxy for your service; the config.web file for configuration settings, and the .disco file
for service discovery. Once you compile the class your assembly will be stored as
*CPPWebService.dll*
in the /bin directory.

I wanted to mimic the C# WebService created in my [previous article](/webservices/myservice.asp),
but with a few minor changes to illustrate using value and reference types.
With this in mind I defined a Value Type structure `ClientData`  and
a managed reference type `ClientInfo` within the namespace that would
both contain a
name and an ID (`string` and `int` values respectively). 

```C++
__value public struct ClientData
{
    String *Name;
    int    ID;
};

__gc public class ClientInfo
{
    String *Name;
    int    ID;
};
```
In order to return an array of objects a quick typedef is also declared

```C++
typedef ClientData ClientArray[];
```
In a similar fashion  I defined my `MyService` class as a simple managed C++
class with three methods:

- `MyMethod is a simple method that `returns a single integer
- `GetClientData` returns a single  `ClientData` 
    structure
- `GetClientsData` returns an array of `ClientInfo `objects

```C++
// CPPWebService.h

#pragma once
#using "System.EnterpriseServices.dll"

namespace CPPWebService
{
__value public struct ClientData
{
    String *Name;
    int    ID;
};

__gc public class ClientInfo
{
    String *Name;
    int    ID;
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
```
The important thing to notice about the function prototypes
is the `[WebMethod]` attribute - this informs the compiler that the method will be a method of a
web service, and that it should provide the appropriate support and plumbing. The method you attach this
attribute to must also be publicly accessible.

The implementation (.cpp) file is as follows.

```C++
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
```
Note the use of the syntax `i.ToString()`. In .NET, value types such as int's and enums can
have methods associated with them. `i.ToString()` simply calls the `Int32::ToString()`
for the variable *i*. 

One huge improvement of .NET beta 2 over beta 1 is that you no longer need to
mess around with the `XmlIncludeAttribute` class to inform the serializer
about your structure. A few bugs that either caused things to misbehave, or
worse - not run altogether - have also been fixed. Writing a WebService in MC++
is now just as easy in C++ as it is in C#, with the advantage that you can mix
and match native and managed code while retaining the raw power of C++. 

Once you have the changes in place you can build the project then test the service by right clicking
on the *CPPWebService.asmx* in the Solution Explorer in Visual Studio and
choosing "View in Browser". The test page is shown below.

![myCPPService](https://raw.githubusercontent.com/ChrisMaunder/mycppservice/master/docs/assets/asmx_page.GIF)

Clicking on one of the methods (say, `GetClientsData`) results in a
proxy page being presented which allows you to invoke the method directly from
your browser. The `GetClientsData` method takes a single `int `parameter
which you can enter in the edit box.

![myCPPService](https://raw.githubusercontent.com/ChrisMaunder/mycppservice/master/docs/assets/test_webmethod.GIF)

When invoked this returns the following:

![](https://raw.githubusercontent.com/ChrisMaunder/mycppservice/master/docs/assets/result.gif)

## Conclusion

Writing WebServices using Visual C++ with managed extensions is just as easy as writing them using C# or VB.NET,
as long as you remember a few simple things: use attributes, declare your classes as managed and make them
publicly accessible. Using the Visual Studio.NET wizards makes
writing and deploying these services a point and click affair, but even if you wish
to do it by hand then the steps involved are extremely simple.

## History

Oct 18 - updated for .NET beta 2
