#include "efi.h"

#include "core_globals.h"
#include "n_iostream.h"
#include "n_heap.h"
#include "n_out_g_stream.h"

#include "RasterFont.h"

#include "includebin.h"

Image windowBuffer;
Pixel* screenBuffer;

extern "C" int atexit(void (*func)())
{
	//nothing...
	return 0;
}

RasterFont* defaultFont;
OutGStream rgcout;

class NWindow
{
	NWindow* children;
};

void exitBootServices()
{
	EFI_STATUS result;
	UINTN mapSize = 0, mapKey, descriptorSize;
	UINT32 descriptorVersion;
	// Get the required memory pool size for the memory map...
	result = BootServices->GetMemoryMap(&mapSize, MemoryMap, nullptr, &descriptorSize, nullptr);
	
	// Allocating the pool creates at least one new descriptor... for the chunk of memory changed to EfiLoaderData
	// Not sure that UEFI firmware must allocate on a memory type boundry... if not, then two descriptors might be created
	mapSize += 2 * descriptorSize;
	// Get a pool of memory to hold the map...
	result = BootServices->AllocatePool(EfiLoaderData, mapSize, (void**)&MemoryMap);
	if (result != EFI_SUCCESS) pink_screen_of_death(1002);

	// Get the actual memory map...
	result = BootServices->GetMemoryMap(&mapSize, MemoryMap, &mapKey, &descriptorSize, &descriptorVersion);
	if (result != EFI_SUCCESS) pink_screen_of_death(1003);

	result = BootServices->ExitBootServices(EfiHandle, mapKey);
	if (result != EFI_SUCCESS) pink_screen_of_death(1004);
}

void showTextModes()
{
	UINTN i = 0;
	UINTN columns;
	UINTN rows;

	rcout << L"Text modes:\r\n";
	while (ConOut->QueryMode(ConOut, i, &columns, &rows) == EFI_SUCCESS)
	{
		rcout << i << L": " << columns << L" x " << rows << L"\r\n";
		i++;
	}
}

void initializeGop()
{
	BootServices->LocateHandleBuffer(ByProtocol,
		&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID,
		nullptr,
		&handleCount,
		&handleBuffer);
	BootServices->HandleProtocol(
		handleBuffer[0],
		&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID,
		(VOID**)&(Gop));

	//Blt exmaples:
	//Gop->Blt(Gop, windowBuffer.data, EfiBltBufferToVideo, 0, 0, 0, 0, 640, 640/*896, 504*/, 1024 * sizeof(Pixel));
	//Gop->Blt(Gop, (Pixel*)windowBuffer.data, EfiBltBufferToVideo, 0, 0, 0, 0, 1024, 768, 0);
}

void initializeMp()
{
	BootServices->LocateHandleBuffer(ByProtocol,
		&EFI_MP_SERVICES_PROTOCOL_GUID,
		nullptr,
		&handleCount,
		&handleBuffer);
	BootServices->HandleProtocol(
		handleBuffer[0],
		&EFI_MP_SERVICES_PROTOCOL_GUID,
		(VOID**)&(MpServices));
}

void initializeFileSystem()
{
	//BootServices->LocateHandleBuffer(ByProtocol,
	//	&EFI_FILE_SYSTEM_PROTOCOL_GUID,
	//	nullptr,
	//	&handleCount,
	//	&handleBuffer);
	//BootServices->HandleProtocol(
	//	handleBuffer[0],
	//	&EFI_FILE_SYSTEM_PROTOCOL_GUID,
	//	(VOID**)&(FileSystem));

		//EFI_FILE_PROTOCOL* Root;
	//FileSystem->OpenVolume(FileSystem, &Root);
}

void ap(void*)
{
	int k = 255;

	while (true)
	{
		for (int y = 0; y < windowBuffer.size.y; y++)
			for (int x = 0; x < windowBuffer.size.x; x++)
				windowBuffer(x, y).Red++;
	}

}

using ApFunction = void(*)(void* arg);

void startAll(ApFunction f)
{
	EFI_EVENT myEvent;
	BootServices->CreateEvent(EVT_RUNTIME, TPL_APPLICATION, nullptr, nullptr, &myEvent);
	UINTN* failed;
	MpServices->StartupAllAPs(MpServices, f, false, myEvent, 0, (void*)nullptr, &failed);
}

void startOne(int num, ApFunction f)
{
	EFI_EVENT myEvent;
	BootServices->CreateEvent(EVT_RUNTIME, TPL_APPLICATION, nullptr, nullptr, &myEvent);
	bool failed;
	MpServices->StartupThisAP(MpServices, f, num, myEvent, 0, (void*)nullptr, &failed);
}

void showGraphicsModes()
{
	rgcout << L"Graphics modes:\r\n";
	UINTN i = 0;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info;
	UINTN sizeofinfo;
	while (Gop->QueryMode(Gop, i, &sizeofinfo, &info) == EFI_SUCCESS)
	{
		rgcout << i << L": " << info->HorizontalResolution << L" x " << info->VerticalResolution << L"\r\n";
		i++;
	}
}

void showProcessors()
{
	UINTN procNum, enabledNum;
	MpServices->GetNumberOfProcessors(MpServices, &procNum, &enabledNum);
	rgcout << L"proc: " << procNum << L"; enabled: " << enabledNum << L"\r\n";

	EFI_PROCESSOR_INFORMATION procInfo;
	for (size_t i = 0; i < procNum; i++)
	{
		MpServices->GetProcessorInfo(MpServices, i, &procInfo);
		rgcout << i << L": " << procInfo.StatusFlag << L"\r\n";
	}
}

int main(EFI_HANDLE handle, EFI_SYSTEM_TABLE* table)
{
	EfiHandle = handle;
	EfiTable = table;
	ConOut = table->ConOut;
	ConIn = table->ConIn;
	BootServices = table->BootServices;

	ConOut->SetMode(ConOut, 0);
	ConOut->SetAttribute(ConOut, EFI_BRIGHT | EFI_WHITE | EFI_BACKGROUND_MAGENTA);

	ConOut->ClearScreen(ConOut);		
	ConOut->EnableCursor(ConOut, true);

	ConOut->OutputString(ConOut, L"Starting NyashkoOS...\r\n");

	initializeGop();
	Gop->SetMode(Gop, 4);
	windowBuffer = matrix<Pixel>(Gop->Mode->Info->HorizontalResolution, Gop->Mode->Info->VerticalResolution);
	screenBuffer = (Pixel*)Gop->Mode->FrameBufferBase;
	//windowBuffer.size.x = Gop->Mode->Info->HorizontalResolution;
	//windowBuffer.size.y = Gop->Mode->Info->VerticalResolution;
	//windowBuffer.data = (Pixel*)Gop->Mode->FrameBufferBase;


	defaultFont = new RasterFont(__FONT);

	for (int y = 0; y < __WALLPAPER.height; y++)
		for (int x = 0; x < __WALLPAPER.width; x++)
			windowBuffer(x, y) = __WALLPAPER(x, y);

	rgcout = OutGStream(windowBuffer, *defaultFont);

	rgcout << L"Version:\r\n";
	rgcout << L"12:30" << L"\r\n";

	initializeMp();

	showProcessors();

	startAll(ap);

	//exitBootServices();

	rgcout.coord = rgcout.minCoord;


	//set wallpaper with scaling
	{
		float scaleInvX = (float)__WALLPAPER.width / windowBuffer.size.x;
		float scaleInvY = (float)__WALLPAPER.height / windowBuffer.size.y;

		if (scaleInvX > scaleInvY)
			scaleInvY = scaleInvX;
		else scaleInvX = scaleInvY;
		

		for (size_t y = 0; y < windowBuffer.size.y; y++)
			for (size_t x = 0; x < windowBuffer.size.x; x++)
			{
				size_t wpx = (size_t)(x * scaleInvX);
				size_t wpy = (size_t)(y * scaleInvY);

				//if (wpx < __WALLPAPER.width && wpy < __WALLPAPER.height)
					windowBuffer(x, y) = __WALLPAPER(wpx, wpy);
			}
	}


	while (true)
	{

		for (size_t y = 0; y < windowBuffer.size.y; y++)
			for (size_t x = 0; x < windowBuffer.size.x; x++)
				screenBuffer[y * windowBuffer.size.x + x] = windowBuffer(x, y);

		//static EFI_INPUT_KEY key;
		//if (ConIn->ReadKeyStroke(ConIn, &key) == EFI_SUCCESS)
			//if (key.UnicodeChar == 'y' || key.UnicodeChar == 'n')
			{
			//rgcout << L'a';// key.UnicodeChar;

				//refresh screen
				//Gop->Blt(Gop, (Pixel*)windowBuffer.data, EfiBltBufferToVideo, rgcout.minCoord.x, rgcout.minCoord.y,
				//	rgcout.minCoord.x, rgcout.minCoord.y, rgcout.maxCoord.x - rgcout.minCoord.x, rgcout.maxCoord.y - rgcout.minCoord.y, 1024*sizeof(Pixel));


				//for (int y = rgcout.minCoord.y; y < rgcout.maxCoord.y; y++)
				//	for (int x = rgcout.minCoord.x; x < rgcout.maxCoord.x; x++)
				//		screen[windowBuffer.size.x * y + x] = windowBuffer(x, y);


				//system->exitmode = key.UnicodeChar;
				//system->exitcode = 0;
			}
	}

	return 0;
}

