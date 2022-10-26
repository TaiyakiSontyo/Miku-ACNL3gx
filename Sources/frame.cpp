#include "ctrulib/srv.h"
#include "ctrulib/result.h"
#include "ctrulib/ipc.h"
#include "cheats.hpp"
#include "mcuhwc.h"
#include "mii.h"
#include "frd.h"
#include "time.h"

namespace CTRPluginFramework
{
	static Handle frdHandle;
	static int frdRefCount;
	typedef struct
	{
		u32 principalId;
		u32 padding;
		u64 localFriendCode;
	} FriendKey;
    void frdInit(void)
    {
        Result ret = 0;

        ret = srvGetServiceHandle(&frdHandle, "frd:a");
        if (R_FAILED(ret)) ret = srvGetServiceHandle(&frdHandle, "frd:n");
        if (R_FAILED(ret)) ret = srvGetServiceHandle(&frdHandle, "frd:u");
        if (R_FAILED(ret)) AtomicDecrement(&frdRefCount);
    }
    void frdExit(void)
    {
        if (AtomicDecrement(&frdRefCount)) return;
        svcCloseHandle(frdHandle);
    }
    Result FRD_GetMyFriendKey(FriendKey *key)
    {
        Result ret = 0;
        u32 *cmdbuf = getThreadCommandBuffer();

        cmdbuf[0] = IPC_MakeHeader(0x05,0,0); // 0x50000

        if (R_FAILED(ret = svcSendSyncRequest(frdHandle))) return ret;

        memcpy(key, &cmdbuf[2], sizeof(FriendKey));

        return (Result)cmdbuf[1];
    }
    Result FRD_PrincipalIdToFriendCode(u32 principalId, u64 *friendCode)
    {
        Result ret = 0;
        u32 *cmdbuf = getThreadCommandBuffer();

        cmdbuf[0] = IPC_MakeHeader(0x24,1,0); // 0x240040
        cmdbuf[1] = principalId;

        if (R_FAILED(ret = svcSendSyncRequest(frdHandle))) return ret;

        *friendCode = (((u64)cmdbuf[3]) << 32 | (u64)cmdbuf[2]);

        return (Result)cmdbuf[1];
    }
	static Handle mcuHwcHandle;
	static int mcuHwcRefCount;

	Result mcuHwcInit(void)
	{
		if (AtomicPostIncrement(&mcuHwcRefCount)) return 0;
		Result res = srvGetServiceHandle(&mcuHwcHandle, "mcu::HWC");
		if (R_FAILED(res)) AtomicDecrement(&mcuHwcRefCount);
		return res;
	}

	void mcuHwcExit(void)
	{
		if (AtomicDecrement(&mcuHwcRefCount)) return;
		svcCloseHandle(mcuHwcHandle);
	}

	Result MCUHWC_ReadRegister(u8 reg, void* data, u32 size)
	{
		Result ret = 0;
		u32 *cmdbuf = getThreadCommandBuffer();

		cmdbuf[0] = IPC_MakeHeader(0x1,2,2); // 0x10082
		cmdbuf[1] = reg;
		cmdbuf[2] = size;
		cmdbuf[3] = IPC_Desc_Buffer (size, IPC_BUFFER_W);
		cmdbuf[4] = (u32)data;

		if(R_FAILED(ret = svcSendSyncRequest(mcuHwcHandle)))return ret;

		return (Result)cmdbuf[1];
	}

	bool fovbool = false;
	bool save = false;

	const std::string g_Empty = "-Empty-";

	bool FCLoaded = false;

	void StoreFC(std::string &FC) {
		frdInit();

		FriendKey key;
		FRD_GetMyFriendKey(&key);

		u64 localFriendCode = 0;
		FRD_PrincipalIdToFriendCode(key.principalId, &localFriendCode);

		std::string str = Utils::Format("%012lld", localFriendCode);
		FC = Utils::Format("FC: %s - %s - %s　　Twitter:@TaiyakiSontyo", str.substr(0, 4).c_str(), str.substr(4, 4).c_str(), str.substr(8, 4).c_str());

		frdExit();
	}

	void StoreBatteryPercentage(float &percentage) 
	{
		u8 data[4];
		mcuHwcInit();
		MCUHWC_ReadRegister(0xA, data, 4);

		percentage = data[1] + data[2] / 256.0f;
        percentage = (u32)((percentage + 0.05f) * 10.0f) / 10.0f;

		mcuHwcExit();
	}

	void OnNewFrameCallback(Time ttime) 
	{

		static std::string FC = "";

		if(!FCLoaded) 
		{
			StoreFC(FC);
			FCLoaded = true;
		}

		const FwkSettings &settings = FwkSettings::Get();
        const Screen& TopScreen = OSD::GetTopScreen();
        const Screen& BottomScreen = OSD::GetBottomScreen();
        time_t rawtime;
        struct tm * timeinfo;
        static const char *dayofweek[] = {"日", "月", "火", "水", "木", "金", "土"};
        
		int coordx = 0, coordy1 = 0, coordy2 = 218;
		
		
		TopScreen.DrawRect(coordx, coordy1, 400, 24, settings.BackgroundMainColor, true);
		TopScreen.DrawRect(coordx + 2, coordy1 + 2, 400 - 4, 20 - 2, settings.BackgroundBorderColor, false);
		
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        TopScreen.DrawSysfont(Utils::Format("%04d年%02d月%02d日(%s)　%02d時%02d分%02d秒　バッテリ:",
		timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,dayofweek[timeinfo->tm_wday],
		timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec), coordx + 5, coordy1 + 3);


		float percentage = 0;
		StoreBatteryPercentage(percentage);


		TopScreen.DrawRect(coordx, coordy2, 400, 20, settings.BackgroundMainColor, true);
		TopScreen.DrawRect(coordx + 2, coordy2 + 2, 400 - 4, 20 - 2, settings.BackgroundBorderColor, false);


		TopScreen.DrawSysfont(Utils::Format("　　　%d%%", (u32)percentage), coordx + 290, coordy1 + 3);
		

		TopScreen.DrawSysfont(FC, coordx + 5, coordy2 + 3);
		//TopScreen.DrawSysfont("BETA 2", coordx + 280, coordy2 + 3);
		
		

		coordx = 20, coordy1 = 0, coordy2 = 218;

		BottomScreen.DrawRect(coordx, coordy1, 280, 20, settings.BackgroundMainColor, true);
		BottomScreen.DrawRect(coordx + 2, coordy1 + 2, 280 - 4, 20 - 2, settings.BackgroundBorderColor, false);
	
		BottomScreen.DrawRect(coordx, coordy2, 280, 20, settings.BackgroundMainColor, true);
		BottomScreen.DrawRect(coordx + 2, coordy2 + 2, 280 - 4, 20 - 2, settings.BackgroundBorderColor, false);
		
		BottomScreen.DrawSysfont("Miku-ACNL", coordx + 5, coordy1 + 3);

		BottomScreen.DrawSysfont("Discord たいやき#5374", coordx + 5, coordy2 + 3);
		
	}
}