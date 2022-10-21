#include "cheats.hpp"
#include <CTRPluginFramework.hpp>
#include <iomanip>
#include <sstream>
/*#define        WRITEFLOAT(addr, data)                *(float *)(addr) = data
#define        WRITEFLOAT8(addr, data)      *(vu8*)(addr) = data*/

namespace CTRPluginFramework
{
u32 offset=0;

/***********メモ*************
1. 英語のキーボード入力表示
	std::string moji;
	Keyboard(moji).Open(moji);

2. フォルダ作成
	Directory::Create();
	
3. ファイル作成
	File::Create();

4. ↑の二つの例
	File::Create(フォルダ/ファイル名);
	
5. 	無かったら作成
	if ((Directory::IsExists("ここにファイル名")) == 0 ) {
		
	}
	
6. ファイル名を指定して作成
	std::string filename;
	Keyboard(filename).Open(filename);
	File::Create(Utils::Format("Test Code/%s.bin",filename.c_str()));
	
7. 高度なファイル作成
	void something(MenuEntry *entry)
	{
		if (!Directory::IsExists("Test Code"))
			Directory::Create("Test Code");
		Keyboard key("",{"保存","リストア","削除"});
		File fp;
		int r = key.Open();
		if ( r == 0 ) {
			KeyboardJP key("ファイル名指定");
			std::string filename;
			if(key.Open(filename)!=-1)
			{
				filename += ".bin";
				File::Open(fp,"プレイヤー名/"+filename,File::RWC);
				for(int i=0;i<8;i++)
					fp.Dump(0x88D09BC + 0xFC*i,24);
				fp.Flush(); //保存
				fp.Close();
				
				MessageBox("ダンプ成功", "")();
			}
		}
		else if ( numberselect != -1 ) {
			Directory dir("Test Code");
			StringVector
			list;
			if (dir.ListFiles(list,".bin") == Directory::OPResult::NOT_OPEN) {
				MessageBox("Error!!", "")();
				return;
			}
			if (list.empty()) {
				MessageBox("Error!!", "ファイルが見つかりませんでした。\n先にダンプしてください。")();
				return;
			}
			std::string a;
			if (numberselect == 1) a = "リストアするファイルを選択してください";
			else a="削除するファイルを選択してください。";
			Keyboard keybord(a,list);
			int userChoice = keybord.Open();
			if (userChoice !=-1) {
				if (numberselect == 1) {
					File.Open(fp,"Test Code/"+list[userChoice], File::RWC);
					for (int i=0;i<8;i++)
						fp.Inject(0x88D09BC+0xFC*i,24);
					fp.Flush();
					fp.Close();
					MessageBox("リストアしました")();
				}else{
					File::Remove("Test Code/"+list[userChoice]);
					MessageBox("ファイルを削除しました")();
				}
			}
		}
	}

8.選択肢のやつ
	void test(MenuEntry *entry) {
Keyboard key("",{"選択肢A","選択式B"});
int a = key.Open();
if(a==0)
 {
 Keyboard key("",{"選択肢A+"});
int b = key.Open();
if(b==0)
{
    Process::Write32(0x0C49ED0C , 0x00000001);
Keyboard key({"A++"});
key.Open();
処理
}
 }
if(a==1)
{
Keyboard key("",{"選択肢B+"});
int b = key.Open();
if(b==0)
{
    Process::Write32(0x0C49ED0C , 0x00000001);
}
}

9. フレコ表示
https://github.com/RedShyGuy/Vapecord-ACNL-Plugin/blob/master/libctrpf/source/CTRPluginFrameworkImpl/System/SystemImpl.cpp
https://github.com/devkitPro/libctru/blob/master/libctru/include/3ds/services/frd.h
u64 frdCode;
GetLocalFriendCode(&frdCode);
std::string frdCodeStr = Utils::Format("%04d-%04d-%04d", (frdCode >> 32) & 0xFFFF, (frdCode >> 16) & 0xFFFF), frdCode & 0xFFFF);

10. 充電残量
https://github.com/LumaTeam/Luma3DS/blob/master/sysmodules/rosalina/source/menu.c

**************************/

//////////なんか///////////

bool cheat_code(u32 value, u32 lowerbound, u32 upperbound)
	{
		return value > lowerbound && value < upperbound;
	}
	
bool cheat_code1(u16 value, u16 lowerbound, u16 upperbound)
{
	return value > lowerbound && value < upperbound;
}

/////////////////////////

/////////////////////////////説明//////////////////////////////

void setumei1(MenuEntry *entry)
{ /* 製作者　*/
	Keyboard key("製作者", {"Discord","Twitter","YouTube","Instagram",});
			
	int r = key.Open();
	if ( r == 0 )
		MessageBox("Discord\nたいやき#5374\nserver\nhttps://discord.gg/GTXF665cXG")();
	if ( r == 1 )
		MessageBox("Twitter\n@TaiyakiSontyo\nhttps://twitter.com/TaiyakiSontyo")();
	if ( r == 2 )
		MessageBox("YouTube\nたいやき村長search\nhttps://youtube.com/c/たいやき村長")();
	if ( r == 3 )
		MessageBox("Instagram\ntaiyaki_0307\nhttps://instagram.com/taiyaki_0307")();
}

void setumei2(MenuEntry *entry)
{ /* 説明 */
	Keyboard key("説明", {"アクションの停止方法","髪型変更(男)","髪型変更(女)","髪の毛の色変更"});
			
	int r = key.Open();
	if ( r == 0 ) {
	MessageBox("チートONをオンにして L+↓ でアクションを解除することができます。")();
	}
	if ( r == 1 ) {
	MessageBox("有効な数字を入力しないとバグります\n0:ずっとヤンチャ\n1:スタイリングする\n2:ベテランで\n3:憧れたい\n4:自然が一番\n5:わざとだよ\n6:じっと耐えます\n7:根性で乗り越える\n8:片付けたい\n9:フレッシュで\nA:パーティーだよ\nB:いつかは落ち着く\nC:けだるいゆるさ\nD:誰も寄せつけたくない\nE:デートなんです\nF:ガーリーなゆるさ\n10:ぼさぼさ")();
	}
	if ( r == 2 ) {
	MessageBox("有効な数字を入力しないとバグります\n11:自然が一番\n12:けだるいゆるさ\n13:片付けたい\n14:わざとだよ\n15:スタイリングする\n16:パーティーだよ\n17:憧れたい\n18:ふわっとしたゆるさ\n19:いつかは落ち着く\n1A:フレッシュで\n1B:ベテランで\n1C:根性で乗り越える\n1D:誰も寄せつけたくない\n1E:ずっとヤンチャ\n1F:デートなんです\n20:じっと耐えます\n21:ぼさぼさ")();
	}
	if ( r == 3 ) {
	MessageBox("有効な数字を入力しないとバグります\n0:茶色")();
	}
}

void setumei3(MenuEntry *entry)
{ /* 協力者 */
	Keyboard key("協力者", {"のむさん",});
			
	int r = key.Open();
	if ( r == 0 )MessageBox(
	"のむさん#7891")();
}

/////////////////////////////////////////////////////////////
//                       常時on推奨                        //
/////////////////////////////////////////////////////////////
void cheat1(MenuEntry *entry)
{ /* チートON */
	Process::Write32(offset + 0x002C01C8, 0xE3A08000);
	Process::Write8(offset + 0xAD0158, 0x02);
	Process::Write32(offset + 0x00AD0250, 0x01000000);
	
	offset = 0x32000000;
	Process::Write32(offset + 0x00E15740, 0x45800000);
	
	offset = 0x33000000;
	if (Controller::IsKeysPressed( L + DPadDown ))
	{
		Process::Write32(offset + 0x9A110, 0x060D0600);
		Process::Write32(offset + 0x99FE4, 0x060D0600);
		OSD::Notify("Action " << Color::Yellow << "stop!");
	}

	offset = 0x33000000;
		if (Controller::IsKeysPressed( R + A ))
		{
			Process::Write32(offset + 0x00099FE4, 0x00606000);
		}

	if (Controller::IsKeysPressed( DPadDown + A ))
	{
		Process::Write32(offset + 0x005989FC, 0xEA000019);
	}
	
	offset = 0x32000000;
	Process::Write32(offset + 0x00E15740, 0x45800000);
	Process::Write32(offset + 0x00AD0250, 0x01000000);
	
	offset = 0x00000000;
	if (Controller::IsKeysPressed( DPadUp + A ))
	{
		Process::Write32(offset + 0x005989FC, 0xEA000030);
	}

	offset = 0x00000000;
	if (Controller::IsKeysPressed( Left + A ))
	{
		Process::Write32(offset + 0x005989FC, 0x0A000044);
	}
	
	offset = 0x00000000;
	Process::Write32(offset + 0x0019BFC8, 0xE1A00000);
	Process::Write32(offset + 0x0019C150, 0xE1A00000);
	Process::Write32(offset + 0x0019B9D8, 0xE1A00000);
	Process::Write32(offset + 0x002C01C8, 0xE3A08000);
	Process::Write32(offset + 0x00AD0250, 0x01000000);
	Process::Write32(offset + 0x00AD05C0, 0x00000000);
	
}


void cheat2(MenuEntry *entry)
{ /* 花散らさない */
	Process::Write32(offset + 0x00596890, 0xE3A0001D);
}


void cheat3(MenuEntry *entry)
{ /* 相手通り抜けられる */
	Keyboard key("ONにすることでプレイヤーやNPCを貫通することができます。", {"ON", "OFF"});
			
	int r = key.Open();
	if ( r == 0 ) {
	Process::Write32(offset + 0x00650D80, 0xEA00002D);
	MessageBox("相手貫通ON")();
	}
	if ( r == 1 ) {
	Process::Write32(offset + 0x00650D80, 0xE3A00000);
	MessageBox("相手貫通OFF")();
	}
}

void cheat4(MenuEntry *entry)
{ /* 壁貫通 */
	if (Controller::IsKeysPressed( DPadRight + L ))
	{
		Process::Write32(offset + 0x0064EF0C, 0xEA000052);
		Process::Write32(offset + 0x0064F070, 0xEA000001);
		Process::Write32(offset + 0x0064F0E8, 0xEA000014);
		Process::Write32(offset + 0x0064F19C, 0xE1A00000);
		Process::Write32(offset + 0x0064F1B4, 0xE1A00000);
		Process::Write32(offset + 0x0064F1B8, 0xEA000026);
		OSD::Notify("Through wall " << Color::Yellow << "ON!");
	}
	if (Controller::IsKeysPressed( DPadLeft + L ))
	{
		Process::Write32(offset + 0x0064EEF4, 0xEA000094);
		Process::Write32(offset + 0x0064F1E4, 0xEA000065);
		Process::Write32(offset + 0x0064EF0C, 0x0A000052);
		Process::Write32(offset + 0x0064F070, 0x0A000001);
		Process::Write32(offset + 0x0064F0E8, 0xDA000014);
		Process::Write32(offset + 0x0064F19C, 0xED841A05);
		Process::Write32(offset + 0x0064F1B4, 0xED840A07);
		Process::Write32(offset + 0x0064F1B8, 0x0A000026);
		OSD::Notify("Through wall " << Color::Yellow << "OFF!");
	}
}

void cheat5(MenuEntry *entry)
{ /* 穴に落ちなくなる */
	Process::Write32(offset + 0x00659160, 0xEA000014);
	Process::Write32(offset + 0x006774DC, 0xEA00002D);
}

void cheat6(MenuEntry*entry)
{ /* チートonテスト */
	offset = 0x00000000;
	Process::Write32(offset + 0x596A30, 0xE3A00001);
	Process::Write32(offset + 0x5A0FEC, 0xE1A00000);
	Process::Write32(offset + 0x5A102C, 0xE3A00001);
	Process::Write32(offset + 0x6502C4, 0x03500001);
	Process::Write32(offset + 0x6502DC, 0xE1A00000);
	Process::Write32(offset + 0x650594, 0x01000540);
	Process::Write32(offset + 0x664948, 0xE3A01006);
	Process::Write32(offset + 0x68A074, 0xE3A01016);
	
	Process::Write32(offset + 0xAD0250, 0x01000000);
	
	Process::Write32(offset + 0xAD05C0, 0x00000000);
	
	Process::Write32(offset + 0x59E6D0, 0xEA000003);
	Process::Write32(offset + 0x59E894, 0xEA000010);
	Process::Write32(offset + 0x59FD8C, 0xE1A00000);
	
	Process::Write32(offset + 0x596890, 0xE3A0001E);
	
	offset = 0x32000000;
	Process::Write32(offset + 0xE15740, 0x45800000);
	
	
	offset = 0x00000000;
	if (Process::Read32(offset + 0x0986500, offset) && cheat_code(offset, 0x00000000, 0x00000000))
	{
		Process::Read32(offset + 0x0986500, offset);
		Process::Read32(0x00000044, offset);
		offset = 0x00000000;
		Process::Write32(offset + 0x00838F00, offset);
	}
	offset = 0x00000000;
	if (Process::Read32(offset + 0x0986500, offset) && cheat_code(offset, 0x00000000, 0x00000000))
	{
		Process::Read32(offset + 0x0986500, offset);
		Process::Read32(0x00000048, offset);
		offset = 0x00000000;
		Process::Write32(offset + 0x00838F04, offset);
	}
	
	
}


/////////////////////////////////////////////////////////////
//                           島                            //
/////////////////////////////////////////////////////////////

void sima1(MenuEntry *entry)
{ /* 島にワープ */
	Process::Write32(offset + 0x00948450, 0x00000000);
	Process::Write32(offset + 0x0094A3D0, 0x00010001);
	Process::Write32(offset + 0x00951338, 0x65000000);
}


void sima2(MenuEntry *entry)
{ /* 乗っ取り*/
	Keyboard key("他のプレイヤーを乗っ取ることができます。\n乗っ取ることで他の人を帰らせることができます。(悪用厳禁)", {"1P","2P","3P","4P",});
			
	int r = key.Open();
	if ( r == 0 ) {
	MessageBox("1P乗っ取ったよ")();
	offset = 0x32000000;
	Process::Write32(offset + 0x18440, 0x00000400);
	}
	if ( r == 1 ) {
	MessageBox("2P乗っ取ったよ")();
	offset = 0x32000000;
	Process::Write32(offset + 0x18440, 0x00000401);
	}
	if ( r == 2 ) {
	MessageBox("3P乗っ取ったよ")();
	offset = 0x32000000;
	Process::Write32(offset + 0x18440, 0x00000402);
	}
	if ( r == 3 ) {
	MessageBox("4P乗っ取ったよ")();
	offset = 0x32000000;
	Process::Write32(offset + 0x18440, 0x00000403);
	}
}

void sima3(MenuEntry *entry)
{ /* 視点乗っ取り */
	Keyboard key("他のプレイヤーの視点を乗っ取ることが出来ます。(あんまり実用性無)", {"ON","OFF",});
			
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x0075D7B0, 0xE1500000);
		Process::Write32(offset + 0x0075D7C0, 0x03A00000);
		MessageBox("視点乗っ取りON")();
	}
	
	if ( r == 1 ) {
		Process::Write32(offset + 0x0075D7B0, 0xE3520000);
		MessageBox("視点乗っ取りOFF")();
	}

}

void sima4(MenuEntry *entry)
{ /* 他の人動かす */
	Process::Write32(offset + 0x0075D7B0, 0xE1520000);
	Process::Write32(offset + 0x0075D7C0, 0x03A00000);
}

void sima5(MenuEntry *entry)
{ /* アクション乗っ取り */
	Keyboard key("他の人のアクションを乗っ取ることができます。\n時々乗っ取れないことがあります。", {"1P","2P","3P","4P","ALL",});
			
	int r = key.Open();
	if ( r == 0 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x000184A4, 0x61000000);
		MessageBox("1Pアクション乗っ取り")();
	}
	if ( r == 1 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x000184A4, 0x61000100);
		MessageBox("2Pアクション乗っ取り")();
	}
	if ( r == 2 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x000184A4, 0x61000200);
		MessageBox("3Pアクション乗っ取り")();
	}
	if ( r == 3 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x000184A4, 0x61000300);
		MessageBox("4Pアクション乗っ取り")();
	}
	if ( r == 4 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x000184A4, 0x61000000);
		Process::Write32(offset + 0x000184A4, 0x61000100);
		Process::Write32(offset + 0x000184A4, 0x61000200);
		Process::Write32(offset + 0x000184A4, 0x61000300);
		MessageBox("全員アクション乗っ取り")();
	}
}


void sima7(MenuEntry *entry)
{ /* 島で電気追加 */
	Process::Write32(offset + 0x005B3BA0, 0xE1A00000);
	Process::Write32(offset + 0x005B3BBC, 0xE1000026);
	Process::Write32(offset + 0x005B5E90, 0xE3A0000A);
}

void sima8(MenuEntry *entry)
{ /* 島でフレンド申請 */
	Keyboard key("島でフレンドを交換することが出来ます。\nこの機能を持った人同士でのみ交換可能です。\n\n使い方\n・左下のソパカが出てくるところを押す。\n・プレイヤーの名前のところを押す\nフレンド申請を送る", {"ON","OFF",});
			
	int r = key.Open();
	if ( r == 0 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x00018474, 0x00000008);
		MessageBox("フレンド申請ON")();
	}
	if ( r == 1 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x00018474, 0x00000200);
		MessageBox("フレンド申請OFF")();
	}
}

void sima9(MenuEntry *entry)
{ /* 島のアイテム無料 */
	offset = 0x330DDF1C;
	Process::Write32(offset + 0x00000000, 0x00000000);
}

void sima10(MenuEntry *entry)
{ /* 引き取りBOX機能変更 */
	Process::Write32(offset + 0x006D2F68, 0xE3A00000);
}

void sima11(MenuEntry *entry)
{ /* プレイヤークラッシュ */
	Keyboard key("現在使用不可", {"1P","2P","3P","4P",});
			
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x320184D0, 0xFF670067);
		Process::Write32(offset + 0x3309A110, 0x0606605F);
		MessageBox("1Pクラッシュ完了")();
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x320184D0, 0xFF670167);
		Process::Write32(offset + 0x3309A110, 0x0606605F);
		MessageBox("2Pクラッシュ完了")();
	}
	if ( r == 2 ) {
		Process::Write32(offset + 0x320184D0, 0xFF670267);
		Process::Write32(offset + 0x3309A110, 0x0606605F);
		MessageBox("3Pクラッシュ完了")();
	}
	if ( r == 3 ) {
		Process::Write32(offset + 0x320184D0, 0xFF670367);
		Process::Write32(offset + 0x3309A110, 0x0606605F);
		MessageBox("4Pクラッシュ完了")();
	}
	
}

void sima12(MenuEntry *entry)
{ /* ツアーリセット */
	Process::Write32(offset + 0x00947E08, 0x0404FF00);
}

void sima13(MenuEntry *entry)
{ /* ロボット浮遊 */
	offset = 0x33000000;
	Process::Write32(offset + 0x000A44D4, 0x00000004);
	Process::Write32(offset + 0x000E5B38, 0x01000020);
}

void sima14(MenuEntry *entry)
{ /* ツアー強制終了 */
	Process::Write32(offset + 0x0094A718, 0x01000100);
}

void sima15(MenuEntry *entry)
{ /* ツアー時間無制限 */
	Process::Write32(offset + 0x0094A718, 0x01000000);
}

void sima16(MenuEntry *entry)
{ /* プレイヤー閉じ込め */
	Keyboard key("プレイヤーを閉じ込め位置にワープします。\n\nバグ報告\n指定した座標にプレイヤーがテレポートしない場合があります。\nこのバグは早急に対処します。", {"1P","2P","3P","4P",});
			
	int r = key.Open();
	if ( r == 0 ) {
		offset = 0x33000000;
		Process::Write32(offset + 0x00099F7C, 0x438DCA39);
		Process::Write32(offset + 0x00099F84, 0x43E4002C);
		MessageBox("1Pを閉じ込めたよ")();
	}
	if ( r == 1 ) {
		offset = 0x33000000;
		Process::Write32(offset + 0x00099F7C, 0x436C0936);
		Process::Write32(offset + 0x00099F84, 0x43E4002C);
		MessageBox("2Pを閉じ込めたよ")();
	}
	if ( r == 2 ) {
		offset = 0x33000000;
		Process::Write32(offset + 0x00099F7C, 0x43B87220);
		Process::Write32(offset + 0x00099F84, 0x43E4002C);
		MessageBox("3Pを閉じ込めたよ")();
	}
	if ( r == 3 ) {
		offset = 0x33000000;
		Process::Write32(offset + 0x00099F7C, 0x4396435B);
		Process::Write32(offset + 0x00099F84, 0x43E4002C);
		MessageBox("4Pを閉じ込めたよ")();
	}
}

void sima17(MenuEntry *entry)
{ /* チャット消えない */
	offset = 0x00000000;
	Process::Write32(offset + 0x214538, 0xE1A00000);
}

void sima18(MenuEntry *entry)
{ /* @マーク使用可能 */
	offset = 0x00000000;
	Process::Write32(offset + 0xAD05C0, 0x00000000);
}

void sima19(MenuEntry *entry)
{ /* 文字数制限解除 */
	Process::Write8(offset + 0xAD0158, 0x02);
}

void sima20(MenuEntry *entry)
{ /*強制エラー */
	if (Controller::IsKeysPressed( L + X ))
	{
		offset = 0x32000000;
		Process::Write16(offset + 0x18442, 0x0001);
	}
}

void sima21(MenuEntry *entry)
{ /* チャット乗っ取り */
	if (Controller::IsKeysPressed(0x00000041))
	{
		offset = 0x32000000;
		Process::Write32(offset + 0x00018440, 0x00000000);
		OSD::Notify("1P Done");
	}
		
	if (Controller::IsKeysPressed(0x00000011))
	{
		offset = 0x32000000;
		Process::Write32(offset + 0x00018440, 0x00000001);
		OSD::Notify("2P Done");
	}
	
	if (Controller::IsKeysPressed(0x00000081))
	{
		offset = 0x32000000;
		Process::Write32(offset + 0x00018440, 0x00000002);
		OSD::Notify("3P Done");
	}
	
	if (Controller::IsKeysPressed(0x00000021))
	{
		offset = 0x32000000;
		Process::Write32(offset + 0x00018440, 0x00000003);
		OSD::Notify("4P Done");
	}

}

void sima22(MenuEntry *entry)
{ /* 島のおみやげ変更 */
	offset = 0x33000000;
	Process::Write16(offset + 0x5B810, 0x2083);
	Process::Write16(offset + 0x5B814, 0x2083);
	Process::Write16(offset + 0x5B818, 0x2083);
	Process::Write16(offset + 0x5B81C, 0x2083);
}

void sima23(MenuEntry *entry)
{ /* 透明化 */
	offset = 0x33000000;
	Process::Write32(offset + 0x9A824, 0x00000000);
	Process::Write32(offset + 0x9A6F8, 0x00000000);
}

void sima24(MenuEntry *entry)
{ /* */
	Keyboard key("自分と同じ動作をさせます", {"1P","2P","3P","4P","解除",});
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x62764C, 0xE3A01000);
		Process::Write32(offset + 0x675FFC, 0xE1A00000);
		MessageBox("1P ON")();
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x62764C, 0xE3A01001);
		Process::Write32(offset + 0x675FFC, 0xE1A00000);
		MessageBox("2P ON")();
	}
	if ( r == 2 ) {
		Process::Write32(offset + 0x62764C, 0xE3A01002);
		Process::Write32(offset + 0x675FFC, 0xE1A00000);
		MessageBox("3P ON")();
	}
	if ( r == 3 ) {
		Process::Write32(offset + 0x62764C, 0xE3A01003);
		Process::Write32(offset + 0x675FFC, 0xE1A00000);
		MessageBox("4P ON")();
	}
	if ( r == 4 ) {
		Process::Write32(offset + 0x62764C, 0xE5D11268);
		Process::Write32(offset + 0x675FFC, 0x1A000017);
		MessageBox("解除")();
	}
}

void sima25(MenuEntry *entry)
{
	offset = 0x32000000;
	Process::Write8(offset + 0x184D3, 0x000000B9);
}

void sima26(MenuEntry *entry)
{
	offset = 0x32000000;
	Keyboard key("乗っ取るプレイヤーを変更します\n1P\n2P\n3P\n4P", {"1P","2P","3P","4P",});
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write8(offset + 0x184D1, 0x00000000);
		MessageBox("1Pを乗っ取ったよ")();
	}
	if ( r == 1 ) {
		Process::Write8(offset + 0x184D1, 0x00000001);
		MessageBox("2Pを乗っ取ったよ")();
	}
	if ( r == 2 ) {
		Process::Write8(offset + 0x184D1, 0x00000002);
		MessageBox("3Pを乗っ取ったよ")();
	}
	if ( r == 3 ) {
		Process::Write8(offset + 0x184D1, 0x00000003);
		MessageBox("4Pを乗っ取ったよ")();
	}
}

void sima27(MenuEntry *entry)
{
	offset = 0x32000000;
	Process::Write8(offset + 0x184D0, 0x00000067);
}

void sima28(MenuEntry *entry)
{
	if(Controller::IsKeysPressed( L + DPadUp ))
	{
		offset = 0x33000000;
		Process::Write32(offset + 0x9A702, 0x67DEF77);
		OSD::Notify("Moon jump " << Color::Yellow << "ON!");
	}
	if(Controller::IsKeysPressed( L + DPadDown ))
	{
		offset = 0x33000000;
		Process::Write32(offset + 0x9A702, 0x600C871);
		OSD::Notify("Moon jump " << Color::Yellow << "OFF!");
	}
}

/////////////////////////////////////////////////////////////
//                          アイテム                         //
/////////////////////////////////////////////////////////////

void item1(MenuEntry *entry)
{
	Keyboard key("拾い方変更\n01: 何でも拾う\n02: 何でも捨てる\n03: 何でも見せびらかす\n04: 解除", {"01: 何でも拾う","02: 何でも捨てる","03: 何でも見せびらかす","04: 元に戻す",});
			
	int r = key.Open();
	if ( r == 0 ) {
	Process::Write32(offset + 0x005989FC, 0xEA000030);
	MessageBox("何でも拾うON")();
	}
	if ( r == 1 ) {
	Process::Write32(offset + 0x005989FC, 0xEA000019);
	MessageBox("何でも捨てるON")();
	}
	if ( r == 2 ) {
	Process::Write32(offset + 0x00661D4C, 0xE3A01092);
	MessageBox("何でも見せびらかすON")();
	}
	if ( r == 3 ) {
	Process::Write32(offset + 0x005989FC, 0x0A000044);
	Process::Write32(offset + 0x00661D4C, 0xE3A0103D);
	MessageBox("元に戻したよ")();
	}
}

void item2(MenuEntry *entry)
{
	Process::Write32(offset + 0x00597D94, 0xE1A00000);
}

void item3(MenuEntry *entry)
{
	Keyboard key("木切れない", {"ON","OFF",});
			
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x00597D98, 0xE3A06000);
		MessageBox("木切れないON")();
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x00597D98, 0xE1A00000);
		MessageBox("木切れないOFF")();
	}
}

void item4(MenuEntry *entry)
{
	Keyboard key("ポケットからアイテム置いたときにアイテムが残ります", {"ON","OFF",});
			
	int r = key.Open();
	if ( r == 0 ) {
	Process::Write32(offset + 0x19C42C, 0x00000000);
	Process::Write32(offset + 0x19C4D0, 0x00000000);
	MessageBox("ON")();
	}
	if ( r == 1 ) {
	Process::Write32(offset + 0x19C42C, 0xEB057D33);
	Process::Write32(offset + 0x19C4D0, 0xEB057D0A);
	MessageBox("OFF")();
	}
}

void item5(MenuEntry *entry)
{
	if (Controller::IsKeysPressed( X + DPadDown ))
	{
		Keyboard key(Color::White << "アイテムの置き方変更\n" << "0.解除\nアイテムの置き方を解除します。\n" << "1.歩いたところを消す\n歩いたところを消します。\n" << "2.Yでポケットの16番目を置く\nYでポケットの16番目のものを地面に置きます。", {"0.解除","1.歩いたところを消す","2.Yでポケットの16番目を置く"});
		{	
			int r = key.Open();
			if ( r == 0 ) {
				Process::Write32(offset + 0x00596890, 0xE3A0001D);
			}
			if ( r == 1 ) {
				Process::Write32(offset + 0x00596890, 0xEA00001D);
			}
			if ( r == 2 ) {
				 if (Controller::IsKeysPressed( Y ))
				 {
				Process::Write32(offset + 0x0032251C, 0xE3A00001);
				Process::Write32(offset + 0x005988E0, 0xEA000008);
				Process::Write32(offset + 0x005989FC, 0xEA00003D);
				Process::Write32(offset + 0x00598AF8, 0xE3A04001);
				Process::Write32(offset + 0x00598B84, 0xE3A00001);
				Process::Write32(offset + 0x0059E5DC, 0xEA000004);
				Process::Write32(offset + 0x00660390, 0xE5C48004);
				Process::Write32(offset + 0x00660394, 0xE5CA9013);
				Process::Write32(offset + 0x006603B8, 0xE3A0103D);
				Process::Write32(offset + 0x00660E20, 0xE3A01006);
				Process::Write32(offset + 0x005976D4, 0xE3A00001);
				Process::Write32(offset + 0x00598908, 0xE3A00001);
				Process::Write32(offset + 0x00598AF8, 0xE3A04001);
				Process::Write32(offset + 0x00598B84, 0xE3A00001);
				Process::Write32(offset + 0x006603B8, 0xE3A0103D);
				Process::Write32(offset + 0x0066F30C, 0xE3A0103D);
				 }
			}
		}
	}
}

void item6(MenuEntry *entry)
{
	Keyboard key("ポケットのアイテムを動かして置く\nポケットのアイテムを1マスずらすと何でも置く", {"ON"});
			
	int r = key.Open();
	if ( r == 0 ) {
	offset = 0x32000000;
	Process::Write32(offset + 0xE1E5A4, 0x32E1A360);
	Process::Write32(offset + 0xE2AB4C, 0x32E26908);
	}
}

void item7(MenuEntry *entry)
{
	Process::Write32(offset + 0x19AE14, 0xEA000003);
}

void item8(MenuEntry *entry)
{
	Keyboard key("オートドロップ", {"ON","OFF",});
			
	int r = key.Open();
	if ( r == 0 ) {
	Process::Write32(offset + 0x19C548, 0xE1A00000);
	Process::Write32(offset + 0x19DDE4, 0xE1A00000);
	Process::Write32(offset + 0x19DF08, 0xE1A00000);
	Process::Write32(offset + 0x26F000, 0xE1A00000);
	Process::Write32(offset + 0x30B844, 0xBA000001);
	}
	if ( r == 1 ) {
	Process::Write32(offset + 0x19C548, 0xEB03FB85);
	Process::Write32(offset + 0x19DDE4, 0xEB03F55E);
	Process::Write32(offset + 0x19DF08, 0xEB10FA8C);
	Process::Write32(offset + 0x26F000, 0xEB00B0D7);
	Process::Write32(offset + 0x30B844, 0x13A00000);
	}
}

void item9(MenuEntry *entry)
{
	Keyboard key("置いたもの透明", {"ON","OFF",});
			
	int r = key.Open();
	if ( r == 0 ) {
	Process::Write32(offset + 0x596178, 0xE3A0000F);
	MessageBox("置いたもの透明ON")();
	}
	if ( r == 1 ) {
	Process::Write32(offset + 0x590000, 0xE3530000);
	MessageBox("置いたもの透明OFF")();
	}
}

void item10(MenuEntry *entry)
{
	Process::Write32(offset + 0x596178, 0xE3A0000A);
}

void item11(MenuEntry *entry)
{
	offset = 0x32000000;
	Process::Write32(offset + 0x184E0, 0x00150015);
}

void item12(MenuEntry *entry)
{
	offset = 0x32000000;
	Process::Write32(offset + 0x184E0, 0x00170017);
}

void item13(MenuEntry *entry)
{
	offset = 0x32000000;
	Process::Write32(offset + 0x184E0, 0x001A001A);
}

void item14(MenuEntry *entry)
{
	offset = 0x32000000;
	Process::Write32(offset + 0x184E0, 0x00240024);
}

void item15(MenuEntry *entry)
{
	offset = 0x32000000;
	Process::Write32(offset + 0x184E0, 0x00250025);
}

void item16(MenuEntry *entry)
{
	offset = 0x32000000;
	Process::Write32(offset + 0x184E0, 0x00260026);
}

void item17(MenuEntry *entry)
{
	if (Controller::IsKeysPressed( DPadUp + X + L ))
	{
		Process::Write32(offset + 0x65FA28, 0x41F00000);
		OSD::Notify("Pick up speed " << Color::Yellow << "UP!");
	}
	if (Controller::IsKeysPressed( DPadRight + X + L ))
	{
		Process::Write32(offset + 0x67AD1E, 0x77777777);
		OSD::Notify("Throw away speed " << Color::Yellow << "UP!");
	}
	if (Controller::IsKeysPressed( DPadDown + X + L ))
	{
		Process::Write32(offset + 0x67DCC0, 0x77777777);
		OSD::Notify("Clover speed " << Color::Yellow << "UP!");
	}
}

void item18(MenuEntry *entry)
{
	Keyboard key("アイテムのスピードを変更します。\n01: スコップで掘る\n02: 地面に埋める\n03: 掘り出す\n04: ジョウロ\n05: 網\n06: オノ跳ね返り", {"01","02","03","04","05","06"});
			
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write16(offset + 0x66930A, 0x4040);
		Process::Write16(offset + 0x668D96, 0x4040);
		Process::Write16(offset + 0x6691DA, 0x7777);
		MessageBox("スコップで掘るスピード上昇ON")();
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x65EF50, 0x77777777);
		MessageBox("地面に埋めるスピード上昇ON")();
	}
	if ( r == 2 ) {
		Process::Write32(offset + 0x682470, 0x77777777);
		MessageBox("掘り出すスピード上昇ON")();
	}
	if ( r == 3 ) {
		offset = 0x00000000;
		Process::Write16(offset + 0x669626, 0x4040);
		MessageBox("ジョウロのスピード上昇ON")();
	}
	if ( r == 4 ) {
		offset = 0x00000000;
		Process::Write16(offset + 0x668E8E, 0x4040);
		MessageBox("網のスピード上昇ON")();
	}
	if ( r == 5 ) {
		offset = 0x00000000;
		Process::Write16(offset + 0x671946, 0x7777);
		MessageBox("オノ跳ね返りのスピード上昇ON")();
	}
}

void item19(MenuEntry *entry)
{
	Keyboard key("遊び道具のスピードを変更します。\n01: ピコピコハンマー\n02: 豆\n03: シャボン玉\n04: 風車\n05: 恵方巻,アイス\n06: コーヒー,サイダー\n07: クラッカー", {"01","02","03","04","05","06","07"});
			
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x686234, 0x77777777);
		Process::Write32(offset + 0x6882D8, 0x77777777);
		MessageBox("ピコピコハンマーのスピード上昇ON")();
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x6728F8, 0x77777777);
		MessageBox("豆のスピード上昇ON")();
	}
	if ( r == 2 ) {
		Process::Write32(offset + 0x675F0C, 0x77777777);
		MessageBox("シャボン玉のスピード上昇ON")();
	}
	if ( r == 3 ) {
		Process::Write32(offset + 0x679B68, 0x77777777);
		MessageBox("風車のスピード上昇ON")();
	}
	if ( r == 4 ) {
		Process::Write32(offset + 0x671DD4, 0x77777777);
		MessageBox("恵方巻とアイスのスピード上昇ON")();
	}
	if ( r == 5 ) {
		Process::Write32(offset + 0x67AA18, 0x77777777);
		MessageBox("コーヒーとサイダーのスピード上昇ON")();
	}
	if ( r == 6 ) {
		Process::Write32(offset + 0x67DB00, 0x77777777);
		MessageBox("クラッカーのスピード上昇ON")();
	}
}

void item20(MenuEntry *entry)
{
	Keyboard key("アクション動作のスピードを変更します。\n01: ドアの開閉\n02: 直立呼吸\n03: エリア移動時の自動歩行\n04: 建物から出る\n05: 向きを変えて椅子から降りる\n06: 住人歩行速度\n07: プレイヤー歩行速度", {"01","02","03","04","05","06","07",});
			
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x530070, 0x00000000);
		MessageBox("ドアの開閉のスピード上昇ON")();
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x64D2C8, 0x41C00000);
		MessageBox("直立呼吸のスピード上昇ON")();
	}
	if ( r == 2 ) {
		Process::Write32(offset + 0x64E118, 0x77777777);
		MessageBox("エリア移動時の自動歩行のスピード上昇ON")();
	}
	if ( r == 3 ) {
		Process::Write16(offset + 0x6579EA, 0x7777);
		MessageBox("建物から出る時のスピード上昇ON")();
	}
	if ( r == 4 ) {
		Process::Write32(offset + 0x66BF3C, 0x77777777);
		MessageBox("向きを変えて椅子から降りるのスピード上昇ON")();
	}
	if ( r == 5 ) {
		Process::Write32(offset + 0x6E8868, 0x41800000);
		MessageBox("住人の歩行スピード上昇ON")();
	}
	if ( r == 6 ) {
		Process::Write32(offset + 0x7632B4, 0x43000000);
		MessageBox("プレイヤーの歩行スピード上昇ON")();
	}
}

void item21(MenuEntry *entry)
{
	for (int i = 0; i < 0x00000010; i++)
		{
		Process::Write32(offset + 0x0F50670, 0x00007FFE);
		offset += 0x00000004;
		}
	Keyboard key("ポケットの中身を全て削除します。", {"削除",});
			
	int r = key.Open();
	if ( r == 0 ) {
		offset = 0x31000000;
		for (int i = 0; i < 0x00000010; i++)
		{
			Process::Write32(offset + 0x0AA40E0, 0x00007FFE);
			Process::Write32(offset + 0x0A85360, 0x00007FFE);
			Process::Write32(offset + 0x0A8F7E0, 0x00007FFE);
			Process::Write32(offset + 0x0A99C60, 0x00007FFE);
			offset += 0x00000004;
		}
		MessageBox("ポケットの中身を削除しました。")();
	}
}

void item22(MenuEntry *entry)
{  //アイテムをグループでセット
	Keyboard key("アイテムをグループでセット(フルーツ)\n01: 無限フルーツ\n02: 無限おいしいフルーツ", {"01: 無限フルーツ","02: 無限おいしいフルーツ"});
			
	int r = key.Open();
	if ( r == 0 ) {
	offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x2018);
		Process::Write16(offset + 0xF50674, 0x2019);
		Process::Write16(offset + 0xF50678, 0x201A);
		Process::Write16(offset + 0xF5067C, 0x201B);
		Process::Write16(offset + 0xF50680, 0x201C);
		Process::Write16(offset + 0xF50684, 0x201D);
		Process::Write16(offset + 0xF50688, 0x201E);
		Process::Write16(offset + 0xF5068C, 0x201F);
		Process::Write16(offset + 0xF50690, 0x2020);
		Process::Write16(offset + 0xF50694, 0x2021);
		Process::Write16(offset + 0xF50698, 0x2022);
		Process::Write16(offset + 0xF5069C, 0x2023);
		MessageBox("セット完了")();
	}//無限フルーツ
	if ( r == 1 ) {
	offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x2024);
		Process::Write16(offset + 0xF50674, 0x2025);
		Process::Write16(offset + 0xF50678, 0x2026);
		Process::Write16(offset + 0xF5067C, 0x2027);
		Process::Write16(offset + 0xF50680, 0x2028);
		Process::Write16(offset + 0xF50684, 0x2029);
		MessageBox("セット完了")();
	}//無限おいしいフルーツ
}

void item23(MenuEntry *entry)
{ //道具系
	Keyboard key("アイテムをグループでセット(道具)\n01: 金道具\n02: 銀道具\n03: レンタル道具\n04: マリンスーツ", {"01: 金道具","02: 銀道具","03: レンタル道具","04: マリンスーツ"});
			
	int r = key.Open();
	if ( r == 0 ) {
	offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x334F);
		Process::Write16(offset + 0xF50674, 0x3353);
		Process::Write16(offset + 0xF50678, 0x3357);
		Process::Write16(offset + 0xF5067C, 0x335B);
		Process::Write16(offset + 0xF50680, 0x335F);
		Process::Write16(offset + 0xF50684, 0x3363);
		MessageBox("セット完了")();
	}//金道具
	if ( r == 1 ) {
	offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x334E);
		Process::Write16(offset + 0xF50674, 0x3352);
		Process::Write16(offset + 0xF50678, 0x3356);
		Process::Write16(offset + 0xF5067C, 0x335A);
		Process::Write16(offset + 0xF50680, 0x335E);
		Process::Write16(offset + 0xF50684, 0x3362);
		MessageBox("セット完了")();
	}//銀道具
	if ( r == 2 ) {
	offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x334C);
		Process::Write16(offset + 0xF50674, 0x3350);
		Process::Write16(offset + 0xF50678, 0x3354);
		Process::Write16(offset + 0xF5067C, 0x3358);
		Process::Write16(offset + 0xF50680, 0x335C);
		Process::Write16(offset + 0xF50684, 0x3360);
		Process::Write16(offset + 0xF50688, 0x3364);
		Process::Write16(offset + 0xF5068C, 0x26ED);
		MessageBox("セット完了")();
	}//レンタル
	if ( r == 3 ) {
	offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x26ED);
		Process::Write16(offset + 0xF50674, 0x26EE);
		Process::Write16(offset + 0xF50678, 0x26EF);
		Process::Write16(offset + 0xF5067C, 0x26F0);
		Process::Write16(offset + 0xF50680, 0x26F1);
		Process::Write16(offset + 0xF50684, 0x26F2);
		Process::Write16(offset + 0xF50688, 0x26F3);
		Process::Write16(offset + 0xF5068C, 0x26F4);
		Process::Write16(offset + 0xF50690, 0x26F5);
		MessageBox("セット完了")();
	}//マリンスーツ
}

void item24(MenuEntry *entry)
{
	Keyboard key("アイテムをグループでセット(サンリオ)\n01: ハローキティ\n02: シナモロール\n03: ポムポムプリン\n04: マイメロディ\n05: キキ&ララ\n06: けろけろけろっぴ", {"01: ハローキティ","02: シナモロール","03: ポムポムプリン","04: マイメロディ","05: キキ&ララ","06: けろけろけろっぴ"});
			
	int r = key.Open();
	if ( r == 0 ) {
		offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x23DE);
		Process::Write16(offset + 0xF50674, 0x2486);
		Process::Write16(offset + 0xF50678, 0x3052);
		Process::Write16(offset + 0xF5067C, 0x3053);
		Process::Write16(offset + 0xF50680, 0x3054);
		Process::Write16(offset + 0xF50684, 0x3055);
		Process::Write16(offset + 0xF50688, 0x3056);
		Process::Write16(offset + 0xF5068C, 0x3057);
		Process::Write16(offset + 0xF50690, 0x3058);
		MessageBox("セット完了")();
	}//ハロキテ
	if ( r == 1 ) {
		offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x23E2);
		Process::Write16(offset + 0xF50674, 0x248A);
		Process::Write16(offset + 0xF50678, 0x306C);
		Process::Write16(offset + 0xF5067C, 0x306D);
		Process::Write16(offset + 0xF50680, 0x306E);
		Process::Write16(offset + 0xF50684, 0x306F);
		Process::Write16(offset + 0xF50688, 0x3070);
		Process::Write16(offset + 0xF5068C, 0x3071);
		MessageBox("セット完了")();
	}//シナモロ
	if ( r == 2 ) {
		offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x23E0);
		Process::Write16(offset + 0xF50674, 0x2488);
		Process::Write16(offset + 0xF50678, 0x305F);
		Process::Write16(offset + 0xF5067C, 0x3060);
		Process::Write16(offset + 0xF50680, 0x3061);
		Process::Write16(offset + 0xF50684, 0x3062);
		Process::Write16(offset + 0xF50688, 0x3063);
		Process::Write16(offset + 0xF5068C, 0x3064);
		Process::Write16(offset + 0xF50690, 0x3065);
		MessageBox("セット完了")();
	}//ポムポム
	if ( r == 3 ) {
		offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x23DF);
		Process::Write16(offset + 0xF50674, 0x2487);
		Process::Write16(offset + 0xF50678, 0x3059);
		Process::Write16(offset + 0xF5067C, 0x305A);
		Process::Write16(offset + 0xF50680, 0x305B);
		Process::Write16(offset + 0xF50684, 0x305C);
		Process::Write16(offset + 0xF50688, 0x305D);
		Process::Write16(offset + 0xF5068C, 0x305E);
		MessageBox("セット完了")();
	}//マイメロ
	if ( r == 4 ) {
		offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x23E1);
		Process::Write16(offset + 0xF50674, 0x2489);
		Process::Write16(offset + 0xF50678, 0x3066);
		Process::Write16(offset + 0xF5067C, 0x3067);
		Process::Write16(offset + 0xF50680, 0x3068);
		Process::Write16(offset + 0xF50684, 0x3069);
		Process::Write16(offset + 0xF50688, 0x306A);
		Process::Write16(offset + 0xF5068C, 0x306B);
		MessageBox("セット完了")();
	}//キキララ
	if ( r == 5 ) {
		offset = 0x31000000;
		Process::Write16(offset + 0xF50670, 0x23E3);
		Process::Write16(offset + 0xF50674, 0x248B);
		Process::Write16(offset + 0xF50678, 0x3072);
		Process::Write16(offset + 0xF5067C, 0x3073);
		Process::Write16(offset + 0xF50680, 0x3074);
		Process::Write16(offset + 0xF50684, 0x3075);
		Process::Write16(offset + 0xF50688, 0x3076);
		Process::Write16(offset + 0xF5068C, 0x3077);
		MessageBox("セット完了")();
	}//けろっぴ
}

void item25(MenuEntry *entry)
{
	if (Controller::IsKeysPressed( Y + R ))
	{
		Process::Read32(offset + 0x94933C, offset);
		Process::Write32(offset + 0x31F50670, offset);
		OSD::Notify(Color::Yellow << "Done!");
	}
}

void item26(MenuEntry *entry)
{
	if (Controller::IsKeysPressed( Y + R ))
	{
		Process::Read32(offset + 0x3041E364, offset);
		Process::Write32(offset + 0x31F50670, offset);
		OSD::Notify(Color::Yellow << "Done!");
	}
}

void item27(MenuEntry *entry)
{
	Process::Write32(offset + 0x64FC94, 0x13A00001);
}

void item28(MenuEntry *entry)
{	
	Process::Write32(offset + 0x7238C0, 0xE1A00000);
}

void item29(MenuEntry *entry)
{
	Process::Write32(offset + 0x32251C, 0xE3A00001);
}

void item30(MenuEntry *entry)
{
	Keyboard key("どんなアイテムもスライドすることで置くことができます\n室内対応",{"ON"});
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x19B504, 0xE3A07000);
		Process::Write32(offset + 0x19CF5C, 0xE1A00000);
	}
}

void item31(MenuEntry *entry)
{
	Keyboard key("物を重ねて置くことができます",{"ON"});
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x0165510, 0xE1A00000);
		Process::Write32(offset + 0x059F8B0, 0x0059FA58);
		Process::Write32(offset + 0x059F8B4, 0x0059FA58);
		Process::Write32(offset + 0x059F8B8, 0x0059FA58);
		Process::Write32(offset + 0x059F8BC, 0x0059FA58);
		Process::Write32(offset + 0x059E6D0, 0xEA000003);
		Process::Write32(offset + 0x059E894, 0xEA000010);
		Process::Write32(offset + 0x059FC2C, 0xE1A00000);
		Process::Write32(offset + 0x059FD8C, 0xE1A00000);
	}
}

void item32(MenuEntry *entry)
{
	Keyboard key("さきゅなりきりセットをポケットに追加します",{"実行"});
	int r = key.Open();
	if ( r == 0 ) {
	offset = 0x31000000;
	Process::Write32(offset + 0x0F50670, 0x00002959);
	Process::Write32(offset + 0x0F50674, 0x00002921);
	Process::Write32(offset + 0x0F50678, 0x0000268A);
	Process::Write32(offset + 0x0F5067C, 0x00002779);
	Process::Write32(offset + 0x0F50680, 0x000027BF);
	Process::Write32(offset + 0x0AA40E0, 0x00002959);
	Process::Write32(offset + 0x0AA40E4, 0x00002921);
	Process::Write32(offset + 0x0AA40E8, 0x0000268A);
	Process::Write32(offset + 0x0AA40EC, 0x00002779);
	Process::Write32(offset + 0x0AA40C0, 0x000027BF);
	Process::Write32(offset + 0x0A85360, 0x00002959);
	Process::Write32(offset + 0x0A85364, 0x00002921);
	Process::Write32(offset + 0x0A85368, 0x0000268A);
	Process::Write32(offset + 0x0A8536C, 0x00002779);
	Process::Write32(offset + 0x0A85370, 0x000027BF);
	Process::Write32(offset + 0x0A8F7E0, 0x00002959);
	Process::Write32(offset + 0x0A8F7E4, 0x00002921);
	Process::Write32(offset + 0x0A8F7E8, 0x0000268A);
	Process::Write32(offset + 0x0A8F7EC, 0x00002779);
	Process::Write32(offset + 0x0A8F7F0, 0x000027BF);
	Process::Write32(offset + 0x0A99C60, 0x00002959);
	Process::Write32(offset + 0x0A99C64, 0x00002921);
	Process::Write32(offset + 0x0A99C68, 0x0000268A);
	Process::Write32(offset + 0x0A99C6C, 0x00002779);
	Process::Write32(offset + 0x0A99C70, 0x000027BF);
	}
}

void item33(MenuEntry *entry)
{
	Keyboard key("花をポケットに追加します\n\n01: バラ\n02: コスモス\n03: チューリップ\n04: パンジー\n05: カーネーション\n06: ユリ\n07: すみれ\n08: その他",{"01: バラ","02: コスモス","03: チューリップ","04: パンジー","05: カーネーション","06: ユリ","07: すみれ","08: その他"});
	int r = key.Open();
	if ( r == 0 ) {
	offset = 0x31000000;
	Process::Write32(offset + 0x0F50670, 0x00002942);
	Process::Write32(offset + 0x0F50674, 0x00002943);
	Process::Write32(offset + 0x0F50678, 0x00002944);
	Process::Write32(offset + 0x0F5067C, 0x00002945);
	Process::Write32(offset + 0x0F50680, 0x00002946);
	Process::Write32(offset + 0x0F50684, 0x00002947);
	Process::Write32(offset + 0x0F50688, 0x00002948);
	Process::Write32(offset + 0x0F5068C, 0x00002949);
	Process::Write32(offset + 0x0F50690, 0x0000294A);
	Process::Write32(offset + 0x0AA40E0, 0x00002942);
	Process::Write32(offset + 0x0AA40E4, 0x00002943);
	Process::Write32(offset + 0x0AA40E8, 0x00002944);
	Process::Write32(offset + 0x0AA40EC, 0x00002945);
	Process::Write32(offset + 0x0AA40C0, 0x00002946);
	Process::Write32(offset + 0x0AA40C4, 0x00002947);
	Process::Write32(offset + 0x0AA40C8, 0x00002948);
	Process::Write32(offset + 0x0AA40CC, 0x00002949);
	Process::Write32(offset + 0x0AA40D0, 0x0000294A);
	Process::Write32(offset + 0x0A85360, 0x00002942);
	Process::Write32(offset + 0x0A85364, 0x00002943);
	Process::Write32(offset + 0x0A85368, 0x00002944);
	Process::Write32(offset + 0x0A8536C, 0x00002945);
	Process::Write32(offset + 0x0A85370, 0x00002946);
	Process::Write32(offset + 0x0A85374, 0x00002947);
	Process::Write32(offset + 0x0A85378, 0x00002948);
	Process::Write32(offset + 0x0A8537C, 0x00002949);
	Process::Write32(offset + 0x0A85380, 0x0000294A);
	Process::Write32(offset + 0x0A8F7E0, 0x00002942);
	Process::Write32(offset + 0x0A8F7E4, 0x00002943);
	Process::Write32(offset + 0x0A8F7E8, 0x00002944);
	Process::Write32(offset + 0x0A8F7EC, 0x00002945);
	Process::Write32(offset + 0x0A8F7F0, 0x00002946);
	Process::Write32(offset + 0x0A8F7F4, 0x00002947);
	Process::Write32(offset + 0x0A8F7F8, 0x00002948);
	Process::Write32(offset + 0x0A8F7FC, 0x00002949);
	Process::Write32(offset + 0x0A8F800, 0x0000294A);
	Process::Write32(offset + 0x0A99C60, 0x00002942);
	Process::Write32(offset + 0x0A99C64, 0x00002943);
	Process::Write32(offset + 0x0A99C68, 0x00002944);
	Process::Write32(offset + 0x0A99C6C, 0x00002945);
	Process::Write32(offset + 0x0A99C70, 0x00002946);
	Process::Write32(offset + 0x0A99C74, 0x00002947);
	Process::Write32(offset + 0x0A99C78, 0x00002948);
	Process::Write32(offset + 0x0A99C7C, 0x00002949);
	Process::Write32(offset + 0x0A99C80, 0x0000294A);
	MessageBox("セット完了")();
	}
	if ( r == 1 ) {
	offset = 0x31000000;
	Process::Write32(offset + 0x0F50670, 0x0000293C);
	Process::Write32(offset + 0x0F50674, 0x0000293D);
	Process::Write32(offset + 0x0F50678, 0x0000293E);
	Process::Write32(offset + 0x0F5067C, 0x0000293F);
	Process::Write32(offset + 0x0F50680, 0x00002940);
	Process::Write32(offset + 0x0F50684, 0x00002941);
	Process::Write32(offset + 0x0AA40E0, 0x0000293C);
	Process::Write32(offset + 0x0AA40E4, 0x0000293D);
	Process::Write32(offset + 0x0AA40E8, 0x0000293E);
	Process::Write32(offset + 0x0AA40EC, 0x0000293F);
	Process::Write32(offset + 0x0AA40C0, 0x00002940);
	Process::Write32(offset + 0x0AA40C4, 0x00002941);
	Process::Write32(offset + 0x0A85360, 0x0000293C);
	Process::Write32(offset + 0x0A85364, 0x0000293D);
	Process::Write32(offset + 0x0A85368, 0x0000293E);
	Process::Write32(offset + 0x0A8536C, 0x0000293F);
	Process::Write32(offset + 0x0A85370, 0x00002940);
	Process::Write32(offset + 0x0A85374, 0x00002941);
	Process::Write32(offset + 0x0A8F7E0, 0x0000293C);
	Process::Write32(offset + 0x0A8F7E4, 0x0000293D);
	Process::Write32(offset + 0x0A8F7E8, 0x0000293E);
	Process::Write32(offset + 0x0A8F7EC, 0x0000293F);
	Process::Write32(offset + 0x0A8F7F0, 0x00002940);
	Process::Write32(offset + 0x0A8F7F4, 0x00002941);
	Process::Write32(offset + 0x0A99C60, 0x0000293C);
	Process::Write32(offset + 0x0A99C64, 0x0000293D);
	Process::Write32(offset + 0x0A99C68, 0x0000293E);
	Process::Write32(offset + 0x0A99C6C, 0x0000293F);
	Process::Write32(offset + 0x0A99C70, 0x00002940);
	Process::Write32(offset + 0x0A99C74, 0x00002941);
	MessageBox("セット完了")();
	}
	if ( r == 2 ) {
	offset = 0x31000000;
	Process::Write32(offset + 0x0F50670, 0x0000292F);
	Process::Write32(offset + 0x0F50674, 0x00002930);
	Process::Write32(offset + 0x0F50678, 0x00002931);
	Process::Write32(offset + 0x0F5067C, 0x00002932);
	Process::Write32(offset + 0x0F50680, 0x00002933);
	Process::Write32(offset + 0x0F50684, 0x00002934);
	Process::Write32(offset + 0x0F50688, 0x00002935);
	Process::Write32(offset + 0x0AA40E0, 0x0000292F);
	Process::Write32(offset + 0x0AA40E4, 0x00002930);
	Process::Write32(offset + 0x0AA40E8, 0x00002931);
	Process::Write32(offset + 0x0AA40EC, 0x00002932);
	Process::Write32(offset + 0x0AA40C0, 0x00002933);
	Process::Write32(offset + 0x0AA40C4, 0x00002934);
	Process::Write32(offset + 0x0AA40C8, 0x00002935);
	Process::Write32(offset + 0x0A85360, 0x0000292F);
	Process::Write32(offset + 0x0A85364, 0x00002930);
	Process::Write32(offset + 0x0A85368, 0x00002931);
	Process::Write32(offset + 0x0A8536C, 0x00002932);
	Process::Write32(offset + 0x0A85370, 0x00002933);
	Process::Write32(offset + 0x0A85374, 0x00002934);
	Process::Write32(offset + 0x0A85378, 0x00002935);
	Process::Write32(offset + 0x0A8F7E0, 0x0000292F);
	Process::Write32(offset + 0x0A8F7E4, 0x00002930);
	Process::Write32(offset + 0x0A8F7E8, 0x00002931);
	Process::Write32(offset + 0x0A8F7EC, 0x00002932);
	Process::Write32(offset + 0x0A8F7F0, 0x00002933);
	Process::Write32(offset + 0x0A8F7F4, 0x00002934);
	Process::Write32(offset + 0x0A8F7F8, 0x00002935);
	Process::Write32(offset + 0x0A99C60, 0x0000292F);
	Process::Write32(offset + 0x0A99C64, 0x00002930);
	Process::Write32(offset + 0x0A99C68, 0x00002931);
	Process::Write32(offset + 0x0A99C68, 0x00002932);
	Process::Write32(offset + 0x0A99C68, 0x00002933);
	Process::Write32(offset + 0x0A99C68, 0x00002934);
	Process::Write32(offset + 0x0A99C68, 0x00002935);	
	MessageBox("セット完了")();
	}
	if ( r == 3 ) {
	offset = 0x31000000;
	Process::Write32(offset + 0x0F50670, 0x00002936);
	Process::Write32(offset + 0x0F50674, 0x00002937);
	Process::Write32(offset + 0x0F50678, 0x00002938);
	Process::Write32(offset + 0x0F5067C, 0x00002939);
	Process::Write32(offset + 0x0F50680, 0x0000293A);
	Process::Write32(offset + 0x0F50684, 0x0000293B);
	Process::Write32(offset + 0x0AA40E0, 0x00002936);
	Process::Write32(offset + 0x0AA40E4, 0x00002937);
	Process::Write32(offset + 0x0AA40E8, 0x00002938);
	Process::Write32(offset + 0x0AA40EC, 0x00002939);
	Process::Write32(offset + 0x0AA40C0, 0x0000293A);
	Process::Write32(offset + 0x0AA40C4, 0x0000293B);
	Process::Write32(offset + 0x0A85360, 0x00002936);
	Process::Write32(offset + 0x0A85364, 0x00002937);
	Process::Write32(offset + 0x0A85368, 0x00002938);
	Process::Write32(offset + 0x0A8536C, 0x00002939);
	Process::Write32(offset + 0x0A85370, 0x0000293A);
	Process::Write32(offset + 0x0A85374, 0x0000293B);
	Process::Write32(offset + 0x0A8F7E0, 0x00002936);
	Process::Write32(offset + 0x0A8F7E4, 0x00002937);
	Process::Write32(offset + 0x0A8F7E8, 0x00002938);
	Process::Write32(offset + 0x0A8F7EC, 0x00002939);
	Process::Write32(offset + 0x0A8F7F0, 0x0000293A);
	Process::Write32(offset + 0x0A8F7F4, 0x0000293B);
	Process::Write32(offset + 0x0A99C60, 0x00002936);
	Process::Write32(offset + 0x0A99C64, 0x00002937);
	Process::Write32(offset + 0x0A99C68, 0x00002938);
	Process::Write32(offset + 0x0A99C6C, 0x00002939);
	Process::Write32(offset + 0x0A99C70, 0x0000293A);
	Process::Write32(offset + 0x0A99C74, 0x0000293B);
	MessageBox("セット完了")();
	}
	if ( r == 4 ) {
	offset = 0x31000000;
	Process::Write32(offset + 0x0F50670, 0x0000294B);
	Process::Write32(offset + 0x0F50674, 0x0000294C);
	Process::Write32(offset + 0x0F50678, 0x0000294D);
	Process::Write32(offset + 0x0AA40E0, 0x0000294B);
	Process::Write32(offset + 0x0AA40E4, 0x0000294C);
	Process::Write32(offset + 0x0AA40E8, 0x0000294D);
	Process::Write32(offset + 0x0A85360, 0x0000294B);
	Process::Write32(offset + 0x0A85364, 0x0000294C);
	Process::Write32(offset + 0x0A85368, 0x0000294D);
	Process::Write32(offset + 0x0A8F7E0, 0x0000294B);
	Process::Write32(offset + 0x0A8F7E4, 0x0000294C);
	Process::Write32(offset + 0x0A8F7E8, 0x0000294D);
	Process::Write32(offset + 0x0A99C60, 0x0000294B);
	Process::Write32(offset + 0x0A99C64, 0x0000294C);
	Process::Write32(offset + 0x0A99C68, 0x0000294D);
	MessageBox("セット完了")();
	}
	if ( r == 5 ) {
	offset = 0x31000000;
	Process::Write32(offset + 0x0F50670, 0x0000294E);
	Process::Write32(offset + 0x0F50674, 0x0000294F);
	Process::Write32(offset + 0x0F50678, 0x00002950);
	Process::Write32(offset + 0x0F5067C, 0x00002951);
	Process::Write32(offset + 0x0F50680, 0x00002952);
	Process::Write32(offset + 0x0F50684, 0x00002953);
	Process::Write32(offset + 0x0AA40E0, 0x0000294E);
	Process::Write32(offset + 0x0AA40E4, 0x0000294F);
	Process::Write32(offset + 0x0AA40E8, 0x00002950);
	Process::Write32(offset + 0x0AA40EC, 0x00002951);
	Process::Write32(offset + 0x0AA40C0, 0x00002952);
	Process::Write32(offset + 0x0AA40C4, 0x00002953);
	Process::Write32(offset + 0x0A85360, 0x0000294E);
	Process::Write32(offset + 0x0A85364, 0x0000294F);
	Process::Write32(offset + 0x0A85368, 0x00002950);
	Process::Write32(offset + 0x0A8536C, 0x00002951);
	Process::Write32(offset + 0x0A85370, 0x00002952);
	Process::Write32(offset + 0x0A85374, 0x00002953);
	Process::Write32(offset + 0x0A8F7E0, 0x0000294E);
	Process::Write32(offset + 0x0A8F7E4, 0x0000294F);
	Process::Write32(offset + 0x0A8F7E8, 0x00002950);
	Process::Write32(offset + 0x0A8F7EC, 0x00002951);
	Process::Write32(offset + 0x0A8F7F0, 0x00002952);
	Process::Write32(offset + 0x0A8F7F4, 0x00002953);
	Process::Write32(offset + 0x0A99C60, 0x0000294E);
	Process::Write32(offset + 0x0A99C64, 0x0000294F);
	Process::Write32(offset + 0x0A99C68, 0x00002950);
	Process::Write32(offset + 0x0A99C6C, 0x00002951);
	Process::Write32(offset + 0x0A99C70, 0x00002952);
	Process::Write32(offset + 0x0A99C74, 0x00002953);
	MessageBox("セット完了")();
	}
	if ( r == 6 ) {
	offset = 0x31000000;
	Process::Write32(offset + 0x0F50670, 0x00002954);
	Process::Write32(offset + 0x0F50674, 0x00002955);
	Process::Write32(offset + 0x0F50678, 0x00002956);
	Process::Write32(offset + 0x0F5067C, 0x00002957);
	Process::Write32(offset + 0x0AA40E0, 0x00002954);
	Process::Write32(offset + 0x0AA40E4, 0x00002955);
	Process::Write32(offset + 0x0AA40E8, 0x00002956);
	Process::Write32(offset + 0x0AA40EC, 0x00002957);
	Process::Write32(offset + 0x0A85360, 0x00002954);
	Process::Write32(offset + 0x0A85364, 0x00002955);
	Process::Write32(offset + 0x0A85368, 0x00002956);
	Process::Write32(offset + 0x0A8536C, 0x00002957);
	Process::Write32(offset + 0x0A8F7E0, 0x00002954);
	Process::Write32(offset + 0x0A8F7E4, 0x00002955);
	Process::Write32(offset + 0x0A8F7E8, 0x00002956);
	Process::Write32(offset + 0x0A8F7EC, 0x00002957);
	Process::Write32(offset + 0x0A99C60, 0x00002954);
	Process::Write32(offset + 0x0A99C64, 0x00002955);
	Process::Write32(offset + 0x0A99C68, 0x00002956);
	Process::Write32(offset + 0x0A99C6C, 0x00002957);
	MessageBox("セット完了")();
	}
	if ( r == 7 ) {
	offset = 0x31000000;
	Process::Write32(offset + 0x0F50670, 0x00002958);
	Process::Write32(offset + 0x0F50674, 0x00002959);
	Process::Write32(offset + 0x0F50678, 0x0000295A);
	Process::Write32(offset + 0x0F5067C, 0x0000295B);
	Process::Write32(offset + 0x0AA40E0, 0x00002958);
	Process::Write32(offset + 0x0AA40E4, 0x00002959);
	Process::Write32(offset + 0x0AA40E8, 0x0000295A);
	Process::Write32(offset + 0x0AA40EC, 0x0000295B);
	Process::Write32(offset + 0x0A85360, 0x00002958);
	Process::Write32(offset + 0x0A85364, 0x00002959);
	Process::Write32(offset + 0x0A85368, 0x0000295A);
	Process::Write32(offset + 0x0A8536C, 0x0000295B);
	Process::Write32(offset + 0x0A8F7E0, 0x00002958);
	Process::Write32(offset + 0x0A8F7E4, 0x00002959);
	Process::Write32(offset + 0x0A8F7E8, 0x0000295A);
	Process::Write32(offset + 0x0A8F7EC, 0x0000295B);
	Process::Write32(offset + 0x0A99C60, 0x00002958);
	Process::Write32(offset + 0x0A99C64, 0x00002959);
	Process::Write32(offset + 0x0A99C68, 0x0000295A);
	Process::Write32(offset + 0x0A99C6C, 0x0000295B);
	MessageBox("セット完了")();
	}
}

void item34(MenuEntry *entry)
{
	Process::Write32(offset+ 0x19BFC8, 0xE1A00000);//部屋に飾る,壁にかける
	Process::Write32(offset+ 0x19C150, 0xE1A00000);//食べる
	Process::Write32(offset+ 0x19B8F8, 0xE1A00000);//地面に植える
	Process::Write32(offset+ 0x19B9D8, 0xE1A00000);//みせびらかす
	Process::Write32(offset+ 0x19BB64, 0xE1A00000);//飲む
	Process::Write32(offset+ 0x19BB08, 0xE1A00000);//タイマーを計る
	Process::Write32(offset+ 0x19BACC, 0xE1A00000);//おサイフにしまう
}

void item35(MenuEntry *entry)
{
	Process::Write32(offset+ 0x19B8C0, 0xE1A00000);//やめるのみ
}

void item36(MenuEntry *entry)
{
	Keyboard key("食べたり埋めたりしてもアイテムが消えなくなります",{"ON","OFF"});
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x32251C, 0xE3A00000);
		MessageBox("ON")();
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x32251C, 0xEB0E5C1D);
		MessageBox("OFF")();
	}
}

void item37(MenuEntry *entry)
{
	Keyboard key("道具の機能を変更します",{"網","スコップ","斧","ジョウロ","元に戻す"});
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x682AA0, 0xE3A01070);
		Process::Write32(offset + 0x67E840, 0xE3A01070);
		Process::Write32(offset + 0x669D28, 0xE3A01070);
		Process::Write32(offset + 0x669D4C, 0xE3A01070);
		Process::Write32(offset + 0x669DA4, 0xE3A01070);
		Process::Write32(offset + 0x669E04, 0xE3A01070);
		MessageBox("全道具の機能を 網 に変更したよ")();
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x682AA0, 0xE3A01049);
		Process::Write32(offset + 0x67E840, 0xE3A01049);
		Process::Write32(offset + 0x669D28, 0xE3A01049);
		Process::Write32(offset + 0x669D4C, 0xE3A01049);
		Process::Write32(offset + 0x669DA4, 0xE3A01049);
		Process::Write32(offset + 0x669E04, 0xE3A01049);
		MessageBox("全道具の機能を スコップ に変更したよ")();
	}
	if ( r == 2 ) {
		Process::Write32(offset + 0x682AA0, 0xE3A01055);
		Process::Write32(offset + 0x67E840, 0xE3A01055);
		Process::Write32(offset + 0x669D28, 0xE3A01055);
		Process::Write32(offset + 0x669D4C, 0xE3A01055);
		Process::Write32(offset + 0x669DA4, 0xE3A01055);
		Process::Write32(offset + 0x669E04, 0xE3A01055);
		MessageBox("全道具の機能を 斧 に変更したよ")();
	}
	if ( r == 3 ) {
		Process::Write32(offset + 0x682AA0, 0xE3A01055);
		Process::Write32(offset + 0x67E840, 0xE3A01055);
		Process::Write32(offset + 0x669D28, 0xE3A01055);
		Process::Write32(offset + 0x669D4C, 0xE3A01055);
		Process::Write32(offset + 0x669DA4, 0xE3A01055);
		Process::Write32(offset + 0x669E04, 0xE3A01055);
		MessageBox("全道具の機能を 斧 に変更したよ")();
	}
	if ( r == 4 ) {
		Process::Write32(offset + 0x682AA0, 0xE3A0106C);
		Process::Write32(offset + 0x67E840, 0xE3A0106C);
		Process::Write32(offset + 0x669D28, 0xE3A0106C);
		Process::Write32(offset + 0x669D4C, 0xE3A0106C);
		Process::Write32(offset + 0x669DA4, 0xE3A0106C);
		Process::Write32(offset + 0x669E04, 0xE3A0106C);
		MessageBox("全道具の機能を ジョウロ に変更したよ")();
	}
	if ( r == 5 ) {
		Process::Write32(offset + 0x682AA0, 0xE3A01049);
		Process::Write32(offset + 0x67E840, 0xE3A010B1);
		Process::Write32(offset + 0x669D28, 0xE3A01070);
		Process::Write32(offset + 0x669D4C, 0xE3A01055);
		Process::Write32(offset + 0x669DA4, 0xE3A0106C);
		Process::Write32(offset + 0x669E04, 0xE3A010A0);
		MessageBox("全道具の機能を元に戻したよ")();
	}
}

void item38(MenuEntry *entry)
{
	Process::Write32(offset + 0x598344, 0xE3A0401C);
}

void item39(MenuEntry *entry)
{
	Process::Write32(offset + 0x598344, 0xE3A0401B);
}

void item40(MenuEntry *entry)
{
	Process::Write32(offset + 0x598344, 0xE3A04013);
}

void item41(MenuEntry *entry)
{
	Process::Write32(offset + 0x598590, 0xE3A0401B);
}

void item42(MenuEntry *entry)
{
	Process::Write32(offset + 0x598590, 0xE3A04012);
}

void item43(MenuEntry *entry)
{
	Process::Write32(offset + 0x598590, 0xE3A04013);
}

void item44(MenuEntry *entry)
{
	Process::Write32(offset + 0x598590, 0xE3A0401C);
}

void item45(MenuEntry *entry)
{
	Process::Write32(offset + 0x5983DC, 0xE3A04012);
}

void item46(MenuEntry *entry)
{
	Process::Write32(offset + 0x5983DC, 0xE3A04013);
}

void item47(MenuEntry *entry)
{
	Process::Write32(offset + 0x5983DC, 0xE3A0401B);
}

void item48(MenuEntry *entry)
{
	Process::Write32(offset + 0x5983DC, 0xE3A0401C);
}

void item49(MenuEntry *entry)
{
	if (Controller::IsKeysPressed( X ))
	{
		Process::Write32(offset + 0x6BD0, 0x00003729);
	}
}

void item50(MenuEntry *entry)
{
	offset = 0x33000000;
	Process::Write32(offset + 0x00001106, 0x000000DF);
}

/////////////////////////////////////////////////////////////
//                           移動                          //
/////////////////////////////////////////////////////////////

void move1(MenuEntry *entry)
{
	Process::Write16(offset + 0x00000000, 0x0000);
	//座標移動未完成
}

void move2(MenuEntry *entry)
{
	offset = 0x33000000;
	if (Controller::IsKeysPressed( A + DPadDown ))
	{
		Process::Write32(offset + 0x99E68, 0x00000000);
	}
	if (Controller::IsKeysPressed( A + DPadRight ))
	{
		Process::Write32(offset + 0x99E68, 0x40000000);
	}
	if (Controller::IsKeysPressed( A + DPadUp ))
	{
		Process::Write32(offset + 0x99E68, 0x80000000);
	}
	if (Controller::IsKeysPressed( A + DPadLeft ))
	{
		Process::Write32(offset + 0x99E68, 0xC0000000);
	}
}

void move3(MenuEntry *entry)
{
	Process::Write32(offset + 0x651708, 0x3F800000);
	if (Controller::IsKeysPressed( B ))
	{
		Process::Write32(offset + 0x651708, 0x40100000);
	}
}

void move4(MenuEntry *entry)
{
	Keyboard key("部屋移動(地上)\n01: 村\n02: 駅\n03: キャンプ場\n04: 役場\n05: Rパーカーズ\n06: モダンな交番\n07: クラシックな交番\n08: カフェ\n09: リセット監視センター\n10: オートキャンプ(左)\n11: オートキャンプ(右)", {"01: 村","02: 駅","03: キャンプ場","04: 役場","05: Rパーカーズ","06: モダンな交番","07: クラシックな交番","08: カフェ","09: リセット監視センター","10: オートキャンプ(左)","11: オートキャンプ(右)"});
			
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x948450, 0x00000100);
		Process::Write32(offset + 0x94A3D0, 0x00010001);
		Process::Write32(offset + 0x951338, 0x00000000);
		MessageBox("村にワープしたよ")();
	}//村
	if ( r == 1 ) {
		Process::Write32(offset + 0x948450, 0x00000100);
		Process::Write32(offset + 0x94A3D0, 0x00010001);
		Process::Write32(offset + 0x951338, 0x02000000);
		MessageBox("駅にワープしたよ")();
	}//駅
	if ( r == 2 ) {
		Process::Write32(offset + 0x948450, 0x00000100);
		Process::Write32(offset + 0x94A3D0, 0x00010001);
		Process::Write32(offset + 0x951338, 0x25000000);
		MessageBox("キャンプ場にワープしたよ")();
	}//キャンプ場
	if ( r == 3 ) {
		Process::Write32(offset + 0x948450, 0x00000100);
		Process::Write32(offset + 0x94A3D0, 0x00010001);
		Process::Write32(offset + 0x951338, 0x26000000);
		MessageBox("役場にワープしたよ")();
	}
	if ( r == 4 ) {
		Process::Write32(offset + 0x948450, 0x00000100);
		Process::Write32(offset + 0x94A3D0, 0x00010001);
		Process::Write32(offset + 0x951338, 0x2B000000);
		MessageBox("Rパーカーズにワープしたよ")();
	}//Rパーカーズ
	if ( r == 5 ) {
		Process::Write32(offset + 0x948450, 0x00000100);
		Process::Write32(offset + 0x94A3D0, 0x00010001);
		Process::Write32(offset + 0x951338, 0x30000000);
		MessageBox("モダンな交番にワープしたよ")();
	}//モダンな交番
	if ( r == 6 ) {
		Process::Write32(offset + 0x948450, 0x00000100);
		Process::Write32(offset + 0x94A3D0, 0x00010001);
		Process::Write32(offset + 0x951338, 0x31000000);
		MessageBox("クラシックな交番にワープしたよ")();
	}//クラシックな交番
	if ( r == 7 ) {
		Process::Write32(offset + 0x948450, 0x00000100);
		Process::Write32(offset + 0x94A3D0, 0x00010001);
		Process::Write32(offset + 0x951338, 0x32000000);
		MessageBox("カフェにワープしたよ")();
	}//カフェ
	if ( r == 8 ) {
		Process::Write32(offset + 0x948450, 0x00000100);
		Process::Write32(offset + 0x94A3D0, 0x00010001);
		Process::Write32(offset + 0x951338, 0x34000000);
		MessageBox("リセット監視センターにワープしたよ")();
	}//リセット監視センター
	if ( r == 9 ) {
		Process::Write32(offset + 0x948450, 0x00000100);
		Process::Write32(offset + 0x94A3D0, 0x00010001);
		Process::Write32(offset + 0x951338, 0x9F000000);
		MessageBox("オートキャンプ(左)にワープしたよ")();
	}
	if ( r == 10 ) {
		Process::Write32(offset + 0x948450, 0x00000100);
		Process::Write32(offset + 0x94A3D0, 0x00010001);
		Process::Write32(offset + 0x951338, 0xA0000000);
		MessageBox("オートキャンプ(右)にワープしたよ")();
	}
}

void move5(MenuEntry *entry)
{
	Keyboard key("通信中ワープ\n01: 島に全員ワープ\n02: 村に全員ワープ",{"01: 島に全員ワープ","02: 村に全員ワープ"});
	
	int r = key.Open();
	if ( r == 0 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184CC, 0x00000263);
		MessageBox("島に全員ワープさせたよ")();
	}
	if ( r == 1 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184CC, 0x0000026A);
		MessageBox("村に全員ワープさせたよ")();
	}
}

void move6(MenuEntry *entry)
{
	Process::Write32(offset + 0x664814, 0xE3A01035);
	offset = 0x33000000;
	if (Process::Read32(0x99F84, offset) && offset != 0xFFFFFFFF)
		u32 offset;
	{
		offset += 0x0000012C;
	}
	Process::Write32(offset + 0x0099FB4, 0x00038000);
	if (Controller::IsKeysPressed( DPadUp + B ))
	{
	Process::Write32(offset + 0x99FB4, 0x00038001);
	Process::Write32(offset + 0x99FB0, 0x00000036);
	Process::Write16(offset + 0x99FE4, 0x0600);
	MessageBox("1Pをワープさせたよ")();
	}
	if (Controller::IsKeysPressed( DPadRight + B ))
	{
	Process::Write32(offset + 0x99FB4, 0x00038001);
	Process::Write32(offset + 0x99FB0, 0x00000036);
	Process::Write16(offset + 0x99FE4, 0x0600);
	MessageBox("2Pをワープさせたよ")();
	}
	if (Controller::IsKeysPressed( DPadDown + B ))
	{
	Process::Write32(offset + 0x99FB4, 0x00038001);
	Process::Write32(offset + 0x99FB0, 0x00000036);
	Process::Write16(offset + 0x99FE4, 0x0600);
	MessageBox("3Pをワープさせたよ")();
	}
	if (Controller::IsKeysPressed( DPadLeft + B ))
	{
	Process::Write32(offset + 0x99FB4, 0x00038001);
	Process::Write32(offset + 0x99FB0, 0x00000036);
	Process::Write16(offset + 0x99FE4, 0x0600);
	MessageBox("4Pをワープさせたよ")();
	}

	Process::Write32(offset + 0x62764C, 0xE5D11268);
	Process::Write32(offset + 0x675FFC, 0x1A000017);

	if (Controller::IsKeysPressed( DPadUp + B ))
	{
		Process::Write32(offset + 0x62764C, 0xE3A01000);
		Process::Write32(offset + 0x675FFC, 0xE1A00000);
	}
	if (Controller::IsKeysPressed( DPadRight + B ))
	{
		Process::Write32(offset + 0x62764C, 0xE3A01001);
		Process::Write32(offset + 0x675FFC, 0xE1A00000);
	}
	if (Controller::IsKeysPressed( DPadDown + B ))
	{
		Process::Write32(offset + 0x62764C, 0xE3A01002);
		Process::Write32(offset + 0x675FFC, 0xE1A00000);
	}
	if (Controller::IsKeysPressed( DPadLeft + B ))
	{
		Process::Write32(offset + 0x62764C, 0xE3A01003);
		Process::Write32(offset + 0x675FFC, 0xE1A00000);
	}
}

/*void move7(MenuEntry *entry)
{
        touchPosition tp;
        hidTouchRead(&tp);
        
        int tch_x = tp.px;
        int tch_y = tp.py;
        
        if (tch_x<70) return;
        if (tch_y<54) return;
        if (tch_x>249) return;
        if (tch_y>206) return;
        
        u32 chk, area;
        Process::Read32(0x3309a374, chk);
        Process::Read32(0x95133a, area);
        if (chk!=2) return;
        
        if (!Controller::IsKeyDown(Touchpad)) return;
        if (Chat::KeyboardOpened()) return;
        if (Emotion::EmotionMenuOpened()) return;
        tch_x -= 70;
        tch_y -= 54;
        if (area==0xa500)
        {
            float kkrX = 13.7;
            float kkrY = 14.8;
            WRITEFLOAT(0x33099e50, (528+(tch_x*kkrX)));
            WRITEFLOAT(0x33099e58, (528+(tch_y*kkrY)));
        }
        else if (area == 0xa568)
        {
            float kkrX = 12;
            float kkrY = 12.6;
            WRITEFLOAT(0x33099e50, (-64+(tch_x*kkrX)));
            WRITEFLOAT(0x33099e58, (125+(tch_y*kkrY)));
        }
}
*/

/////////////////////////////////////////////////////////////
//                         アクション                         //
/////////////////////////////////////////////////////////////

void act1(MenuEntry *entry)
{
	Keyboard key("強制エラーを起こします。\n島での使用などは自己責任で御願いします\n動作が不安定になった場合は気絶で直る可能性があるのでそちらの使用を推奨します。",{"実行"});
	
	int r = key.Open();
	if ( r == 0 ) {
	offset = 0x32000000;
	Process::Write16(offset + 0x0018442, 0x00000001);
	}
}

void act2(MenuEntry *entry)
{
	Process::Write32(offset + 0x47CFFC, 0x40000000);
}

void act3(MenuEntry *entry)
{
	offset = 0x33000000;
	Process::Write32(offset + 0x99FE4, 0x03030D00);
}

void act4(MenuEntry *entry)
{
	offset = 0x33000000;
	if (Controller::IsKeysPressed( X + R ))
	{
		Process::Write32(offset + 0x9A110, 0x06E60600);
	}
}

void act5(MenuEntry *entry)
{
	Keyboard key("Yでアクションを実行します\n01: 綿毛\n02: くしゃみ\n03: みせびらかす\n04: もやもや",{"01: 綿毛","02: くしゃみ","03: みせびらかす","04: もやもや"});
	
	int r = key.Open();
	if ( r == 0 ) {
		if (Controller::IsKeysPressed( Y )) {
		offset = 0x33000000;
		Process::Write32(offset + 0x99FE4, 0x06069000);
		MessageBox("綿毛ON")();
		}
	}
	if ( r == 1 ) {
		if (Controller::IsKeysPressed( Y )) {
		offset = 0x33000000;
		Process::Write32(offset + 0x99FE4, 0x1F202500);
		MessageBox("くしゃみON")();
		}
	}
	if ( r == 2 ) {
		if (Controller::IsKeysPressed( Y )) {
		offset = 0x33000000;
		Process::Write32(offset + 0x99FE4, 0x06069200);
		MessageBox("みせびらかすON")();
		}
	}
	if ( r == 3 ) {
		if (Controller::IsKeysPressed( Y )) {
		offset = 0x33000000;
		Process::Write32(offset + 0x99FE4, 0xC0DAC03C);
		MessageBox("もやもやON")();
		}
	}
}

void act6(MenuEntry *entry)
{
	Keyboard key("Yでアクションを実行します\n01: 無表情\n02: 埋まる\n03: 全身チカチカ\n04: 空気イス",{"01: 無表情","02: 埋まる","03: 全身チカチカ","04: 空気イス"});
	
	int r = key.Open();
	if ( r == 0 ) {
		if (Controller::IsKeysPressed( Y )) {
		offset = 0x33000000;
		Process::Write32(offset + 0x9A110, 0x06636400);
		MessageBox("無表情ON")();
		}
	}
	if ( r == 1 ) {
		if (Controller::IsKeysPressed( Y )) {
		offset = 0x33000000;
		Process::Write32(offset + 0x9A110, 0x0606605F);
		MessageBox("埋まるON")();
		}
	}
	if ( r == 2 ) {
		if (Controller::IsKeysPressed( Y )) {
		offset = 0x33000000;
		Process::Write32(offset + 0x9A110, 0x06181900);
		MessageBox("全身チカチカON")();
		}
	}
	if ( r == 3 ) {
		if (Controller::IsKeysPressed( Y )) {
		offset = 0x33000000;
		Process::Write32(offset + 0x9A110, 0x7C7B7C00);
		MessageBox("空気イスON")();
		}
	}
}

void act7(MenuEntry *entry)
{
	Keyboard key("けんじいのactコマンドと同じです\n実行は歯車から選択して下さい\n\nNo.06はXを1秒以上押し続けてください\nNo.08はXで実行できます\nNo.09はYで実行できます\nNo.21はアミを高速で振れます\nNo.38はL+↑でON,L+↓でOFFになります\nNo.52はXで実行できます",{"No.01 強制エラー","No.02 気絶(室外)","No.03 気絶(室内)","No.06 連続前転","No.08 水中に潜る","No.09 地中から出る","No.17 空気イス","No.21 連続アミ振り","No.24 連続アクション","No.31 エフェクト効果","No.38 どこでも泳ぐ","No.52 連続クラゲ"});
	
	int r = key.Open();
	if ( r == 0 ) {
		offset = 0x32000000;
		Process::Write16(offset + 0x18442, 0x00001010);
		MessageBox("強制エラー")();
	}
	if ( r == 1 ) {
		offset = 0x33000000;
		Process::Write32(offset + 0x0099FB4, 0x00038001);
		Process::Write32(offset + 0x0099FB0, 0x00000036);
		Process::Write16(offset + 0x0099FE4, 0x0600);
		MessageBox("気絶(室外)")();
	}
	if ( r == 2 ) {
		offset = 0x33000000;
		Process::Write32(offset + 0x009A0E0, 0x00038001);
		Process::Write32(offset + 0x009A0DC, 0x00000036);
		Process::Write16(offset + 0x009A118, 0x0600);
		MessageBox("気絶(室内)")();
	}
	if ( r == 3 ) {
		offset = 0x33000000;
		if (Controller::IsKeysPressed( X )) {
		Process::Write32(offset + 0x99FE4, 0x08206000);
		MessageBox("連続前転")();
		}
	}
	if ( r == 4 ) {
		offset = 0x33000000;
		if (Controller::IsKeysPressed( X )) {
		Process::Write32(offset + 0x99FE4, 0x1F212200);
		MessageBox("水中に潜る")();
		}
	}
	if ( r == 5 ) {
		offset = 0x33000000;
		if (Controller::IsKeysPressed( Y )) {
		Process::Write32(offset + 0x99FE4, 0x1F222300);
		MessageBox("地中から出る")();
		}
	}
	if ( r == 6 ) {
		offset = 0x33000000;
		Process::Write32(offset + 0x99FE4, 0x00BBABA0);
		MessageBox("空気イス")();
	}
	if ( r == 7 ) {
		offset = 0x00000000;
		Process::Write16(offset + 0x668E8E, 0x4040);
		MessageBox("連続アミ振り")();
	}
	if ( r == 8 ) {
		offset = 0x33000000;
		Process::Write32(offset + 0x9A110, 0x06200659);
		Process::Write32(offset + 0x99FE4, 0x06200659);
		MessageBox("連続アクション")();
	}
	if ( r == 9 ) {
		Process::Write32(offset + 0x54F3B4, 0x410FFFFF);
		MessageBox("エフェクト効果")();
	}
	if ( r == 10 ) {
		if (Controller::IsKeysPressed( L + DPadUp ))
		{
			Process::Write32(offset + 0x064D324, 0xE3A00001);
			Process::Write32(offset + 0x076225C, 0xE3A00000);
			Process::Write32(offset + 0x0651C4C, 0xE3A00000);
			Process::Write32(offset + 0x0652028, 0xE3A00000);
			OSD::Notify("Swim " << Color::Yellow << "ON!");
		}
		if (Controller::IsKeysPressed( L + DPadDown ))
		{
			Process::Write32(offset + 0x064D324, 0xE3A00000);
			Process::Write32(offset + 0x076225C, 0xE3A00001);
			Process::Write32(offset + 0x0651C4C, 0xEBFC62D8);
			Process::Write32(offset + 0x0652028, 0xEB00AFB7);
			OSD::Notify("Swim " << Color::Yellow << "OFF!");
		}
		MessageBox("どこでも泳ぐ")();
	}
	if ( r == 11 ) {
		offset = 0x33000000;
		if (Controller::IsKeysPressed( X )) {
			Process::Write32(offset + 0x99FE4, 0x1F262700);
			MessageBox("連続クラゲ")();
		}
	}
}

void act8(MenuEntry *entry)
{
	Keyboard key("ネタ系アクション(室外)\n\n01: 流れ星(L+↑で実行)\n02: ハゲ(Yで実行)",{"01: 流れ星","02: ハゲ"});
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x0664814, 0xE3A01039);
		offset = 0x33000000;
		if (Controller::IsKeysPressed( L + DPadUp ))
		{
			if (Process::Read32(offset + 0x99F7C, offset) && offset != 0xFFFFFFFF)
			{
				Process::Write32(offset + 0x9A0E0, 0x00038001);
				Process::Write32(offset + 0x9A0DC, 0x00000036);
				Process::Write16(offset + 0x9A110, 0x0600);
			}
			OSD::Notify("Star" << Color::Yellow << " ON!");
		}
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x0664814, 0xE3A010B9);
		offset = 0x33000000;
		if (Controller::IsKeysPressed( Y ))
		{
			Process::Write32(offset + 0x0099FB4, 0x00038001);
			Process::Write32(offset + 0x0099FB0, 0x00000036);
			Process::Write16(offset + 0x0099FE4, 0x0600);
		}
		MessageBox("ハゲ")();
	}
	
}

void act9(MenuEntry *entry)
{
	Keyboard key("常に動作するアクション\n押すだけで実行されます",{"男歩き","女歩き","男走り","女走り","ききーっ","雪玉","着替え","木を持つ","木を揺らす","ノック","飛び込み","足で消す途中","足で消す","左から右","やったー","尻もち","とぶ","座る","寝る","潜る","落とし穴","気絶"});
	int r =key.Open();
	if ( r == 0 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x000D000D);
		MessageBox("男歩き")();
	}
	if ( r == 1 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x000E000E);
		MessageBox("女歩き")();
	}
	if ( r == 2 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x000F000F);
		MessageBox("男走り")();
	}
	if ( r == 3 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00100010);
		MessageBox("女走り")();
	}
	if ( r == 4 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00110011);
		MessageBox("ききーっ")();
	}
	if ( r == 5 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00120012);
		MessageBox("雪玉")();
	}
	if ( r == 6 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00160016);
		MessageBox("着替え")();
	}
	if ( r == 7 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x002C002C);
		MessageBox("木を持つ")();
	}
	if ( r == 8 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x002D002D);
		MessageBox("木を揺らす")();
	}
	if ( r == 9 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x002E002E);
		MessageBox("ノック")();
	}
	if ( r == 10 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00370037);
		MessageBox("飛び込み")();
	}
	if ( r == 11 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x003E003E);
		MessageBox("足で消す途中")();
	}
	if ( r == 12 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x003F003F);
		MessageBox("足で消す")();
	}
	if ( r == 13 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00500050);
		MessageBox("左から右")();
	}
	if ( r == 14 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00680068);
		MessageBox("やったー")();
	}
	if ( r == 15 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x008B008B);
		MessageBox("尻もち")();
	}
	if ( r == 16 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00A800A8);
		MessageBox("とぶ")();
	}
	if ( r == 17 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00AB00AB);
		MessageBox("座る")();
	}
	if ( r == 18 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00B900B9);
		MessageBox("寝る")();
	}
	if ( r == 19 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00C400C4);
		MessageBox("潜る")();
	}
	if ( r == 20 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00D500D5);
		MessageBox("落とし穴")();
	}
	if ( r == 21 ) {
		offset = 0x33000000;
		Process::Write32(offset + 0x0099FB4, 0x00038001);
		Process::Write32(offset + 0x0099FB0, 0x00000036);
		Process::Write16(offset + 0x0099FE4, 0x0600);
		Process::Write32(offset + 0x009A0E0, 0x00038001);
		Process::Write32(offset + 0x009A0DC, 0x00000036);
		Process::Write16(offset + 0x009A118, 0x0600);
		MessageBox("気絶")();
	}
}

void act10(MenuEntry *entry)
{
	Keyboard key("アクションなどでバグが発生した場合に使用してください\nもし気絶で直らない場合は強制エラーを使用してください",{"実行"});
	int r=key.Open();
	if ( r == 0 ) {
		offset = 0x33000000;
		Process::Write32(offset + 0x0099FB4, 0x00038001);
		Process::Write32(offset + 0x0099FB0, 0x00000036);
		Process::Write16(offset + 0x0099FE4, 0x0600);
		Process::Write32(offset + 0x009A0E0, 0x00038001);
		Process::Write32(offset + 0x009A0DC, 0x00000036);
		Process::Write16(offset + 0x009A118, 0x0600);
		MessageBox("気絶")();
	}
}

void act11(MenuEntry *entry)
{
	Keyboard key("特定のことが発生するアクション\n押すだけで実行されます",{"ハチ","蚊","コケる","くち","回転","首を傾げる","フーっ","面白い","＞＜","早口","座り寝","立ち寝","ケーキの火を消す","浮く","じゃんけん1","じゃんけん2","揺れる","ばあ!?","広場の木","倒れる","バク転","謎の動き"});
	int r =key.Open();
	if ( r == 0 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00DF00DF);
		MessageBox("ハチ")();
	}
	if ( r == 1 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00E400E4);
		MessageBox("蚊")();
	}
	if ( r == 2 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00E600E6);
		MessageBox("コケる")();
	}
	if ( r == 3 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x00FA00FA);
		MessageBox("くち")();
	}
	if ( r == 4 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01060106);
		MessageBox("回転")();
	}
	if ( r == 5 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01110111);
		MessageBox("首を傾げる")();
	}
	if ( r == 6 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x011F011F);
		MessageBox("フーっ")();
	}
	if ( r == 7 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01230123);
		MessageBox("面白い")();
	}
	if ( r == 8 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01240124);
		MessageBox("＞＜")();
	}
	if ( r == 9 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01250125);
		MessageBox("早口")();
	}
	if ( r == 10 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01260126);
		MessageBox("座り寝")();
	}
	if ( r == 11 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01270127);
		MessageBox("立ち寝")();
	}
	if ( r == 12 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01280128);
		MessageBox("ケーキの火を消す")();
	}
	if ( r == 13 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x012C012C);
		MessageBox("うく")();
	}
	if ( r == 14 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01300130);
		MessageBox("じゃんけん1")();
	}
	if ( r == 15 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01310131);
		MessageBox("じゃんけん2")();
	}
	if ( r == 16 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01340134);
		MessageBox("揺れる")();
	}
	if ( r == 17 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01380138);
		MessageBox("ばあ!?")();
	}
	if ( r == 18 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01420142);
		MessageBox("広場の木")();
	}
	if ( r == 19 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01B201B2);
		MessageBox("倒れる")();
	}
	if ( r == 20 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01D701D7);
		MessageBox("バク転")();
	}
	if ( r == 21 ) {
		offset = 0x32000000;
		Process::Write32(offset + 0x184E0, 0x01D801D8);
		MessageBox("謎の動き")();
	}
}

void act12(MenuEntry *entry)
{
	Keyboard key("師匠のアクションコピー\n\nアクション正規の師匠のアクションに変更します。",{"村長(1P)","サブ(2P)","サブ(3P)","サブ(4P)"});
	int r = key.Open();
	if ( r == 0 ) {
		offset = 0x31000000;
		Process::Write8(offset + 0xF52470, 0x01);
		Process::Write8(offset + 0xF52471, 0x02);
		Process::Write8(offset + 0xF52472, 0x03);
		Process::Write8(offset + 0xF52473, 0x04);
		Process::Write8(offset + 0xF52474, 0x05);
		Process::Write8(offset + 0xF52475, 0x06);
		Process::Write8(offset + 0xF52476, 0x07);
		Process::Write8(offset + 0xF52477, 0x08);
		Process::Write8(offset + 0xF52478, 0x09);
		Process::Write8(offset + 0xF52479, 0x0A);
		Process::Write8(offset + 0xF5247A, 0x0B);
		Process::Write8(offset + 0xF5247B, 0x0C);
		Process::Write8(offset + 0xF5247C, 0x0D);
		Process::Write8(offset + 0xF5247D, 0x0E);
		Process::Write8(offset + 0xF5247E, 0x10);
		Process::Write8(offset + 0xF5247F, 0x11);
		Process::Write8(offset + 0xF52480, 0x12);
		Process::Write8(offset + 0xF52481, 0x13);
		Process::Write8(offset + 0xF52482, 0x14);
		Process::Write8(offset + 0xF52483, 0x15);
		Process::Write8(offset + 0xF52484, 0x16);
		Process::Write8(offset + 0xF52485, 0x17);
		Process::Write8(offset + 0xF52486, 0x18);
		Process::Write8(offset + 0xF52487, 0x19);
		Process::Write8(offset + 0xF52488, 0x1A);
		Process::Write8(offset + 0xF52489, 0x1B);
		Process::Write8(offset + 0xF5248A, 0x1C);
		Process::Write8(offset + 0xF5248B, 0x1D);
		Process::Write8(offset + 0xF5248C, 0x1E);
		Process::Write8(offset + 0xF5248D, 0x20);
		Process::Write8(offset + 0xF5248E, 0x21);
		Process::Write8(offset + 0xF5248F, 0x24);
		Process::Write8(offset + 0xF52490, 0x26);
		Process::Write8(offset + 0xF52491, 0x2C);
		Process::Write8(offset + 0xF52492, 0x28);
		Process::Write8(offset + 0xF52493, 0x2A);
		Process::Write8(offset + 0xF52494, 0x27);
		Process::Write8(offset + 0xF52495, 0x29);
		Process::Write8(offset + 0xF52496, 0x2B);
		Process::Write8(offset + 0xF52497, 0x2E);
		MessageBox("1Pのアクションを変更したよ")();
	}
	if ( r == 1 ) {
		offset = 0x31000000;
		Process::Write8(offset + 0xF5C8F0, 0x01);
		Process::Write8(offset + 0xF5C8F1, 0x02);
		Process::Write8(offset + 0xF5C8F2, 0x03);
		Process::Write8(offset + 0xF5C8F3, 0x04);
		Process::Write8(offset + 0xF5C8F4, 0x05);
		Process::Write8(offset + 0xF5C8F5, 0x06);
		Process::Write8(offset + 0xF5C8F6, 0x07);
		Process::Write8(offset + 0xF5C8F7, 0x08);
		Process::Write8(offset + 0xF5C8F8, 0x09);
		Process::Write8(offset + 0xF5C8F9, 0x0A);
		Process::Write8(offset + 0xF5C8FA, 0x0B);
		Process::Write8(offset + 0xF5C8FB, 0x0C);
		Process::Write8(offset + 0xF5C8FC, 0x0D);
		Process::Write8(offset + 0xF5C8FD, 0x0E);
		Process::Write8(offset + 0xF5C8FE, 0x10);
		Process::Write8(offset + 0xF5C8FF, 0x11);
		Process::Write8(offset + 0xF5C900, 0x12);
		Process::Write8(offset + 0xF5C901, 0x13);
		Process::Write8(offset + 0xF5C902, 0x14);
		Process::Write8(offset + 0xF5C903, 0x15);
		Process::Write8(offset + 0xF5C904, 0x16);
		Process::Write8(offset + 0xF5C905, 0x17);
		Process::Write8(offset + 0xF5C906, 0x18);
		Process::Write8(offset + 0xF5C907, 0x19);
		Process::Write8(offset + 0xF5C908, 0x1A);
		Process::Write8(offset + 0xF5C909, 0x1B);
		Process::Write8(offset + 0xF5C90A, 0x1C);
		Process::Write8(offset + 0xF5C90B, 0x1D);
		Process::Write8(offset + 0xF5C90C, 0x1E);
		Process::Write8(offset + 0xF5C90D, 0x20);
		Process::Write8(offset + 0xF5C90E, 0x21);
		Process::Write8(offset + 0xF5C90F, 0x24);
		Process::Write8(offset + 0xF5C910, 0x26);
		Process::Write8(offset + 0xF5C911, 0x2C);
		Process::Write8(offset + 0xF5C912, 0x28);
		Process::Write8(offset + 0xF5C913, 0x2A);
		Process::Write8(offset + 0xF5C914, 0x27);
		Process::Write8(offset + 0xF5C915, 0x29);
		Process::Write8(offset + 0xF5C916, 0x2B);
		Process::Write8(offset + 0xF5C917, 0x2E);
		MessageBox("2Pのアクションを変更したよ")();
	}
	if ( r == 2 ) {
		offset = 0x31000000;
		Process::Write8(offset + 0xF66D70, 0x01);
		Process::Write8(offset + 0xF66D71, 0x02);
		Process::Write8(offset + 0xF66D72, 0x03);
		Process::Write8(offset + 0xF66D73, 0x04);
		Process::Write8(offset + 0xF66D74, 0x05);
		Process::Write8(offset + 0xF66D75, 0x06);
		Process::Write8(offset + 0xF66D76, 0x07);
		Process::Write8(offset + 0xF66D77, 0x08);
		Process::Write8(offset + 0xF66D78, 0x09);
		Process::Write8(offset + 0xF66D79, 0x0A);
		Process::Write8(offset + 0xF66D7A, 0x0B);
		Process::Write8(offset + 0xF66D7B, 0x0C);
		Process::Write8(offset + 0xF66D7C, 0x0D);
		Process::Write8(offset + 0xF66D7D, 0x0E);
		Process::Write8(offset + 0xF66D7E, 0x10);
		Process::Write8(offset + 0xF66D7F, 0x11);
		Process::Write8(offset + 0xF66D80, 0x12);
		Process::Write8(offset + 0xF66D81, 0x13);
		Process::Write8(offset + 0xF66D82, 0x14);
		Process::Write8(offset + 0xF66D83, 0x15);
		Process::Write8(offset + 0xF66D84, 0x16);
		Process::Write8(offset + 0xF66D85, 0x17);
		Process::Write8(offset + 0xF66D86, 0x18);
		Process::Write8(offset + 0xF66D87, 0x19);
		Process::Write8(offset + 0xF66D88, 0x1A);
		Process::Write8(offset + 0xF66D89, 0x1B);
		Process::Write8(offset + 0xF66D8A, 0x1C);
		Process::Write8(offset + 0xF66D8B, 0x1D);
		Process::Write8(offset + 0xF66D8C, 0x1E);
		Process::Write8(offset + 0xF66D8D, 0x20);
		Process::Write8(offset + 0xF66D8E, 0x21);
		Process::Write8(offset + 0xF66D8F, 0x24);
		Process::Write8(offset + 0xF66D90, 0x26);
		Process::Write8(offset + 0xF66D91, 0x2C);
		Process::Write8(offset + 0xF66D92, 0x28);
		Process::Write8(offset + 0xF66D93, 0x2A);
		Process::Write8(offset + 0xF66D94, 0x27);
		Process::Write8(offset + 0xF66D95, 0x29);
		Process::Write8(offset + 0xF66D96, 0x2B);
		Process::Write8(offset + 0xF66D97, 0x2E);
		MessageBox("3Pのアクションを変更したよ")();
	}
	if ( r == 3 ) {
		offset = 0x31000000;
		Process::Write8(offset + 0xF711F0, 0x01);
		Process::Write8(offset + 0xF711F1, 0x02);
		Process::Write8(offset + 0xF711F2, 0x03);
		Process::Write8(offset + 0xF711F3, 0x04);
		Process::Write8(offset + 0xF711F4, 0x05);
		Process::Write8(offset + 0xF711F5, 0x06);
		Process::Write8(offset + 0xF711F6, 0x07);
		Process::Write8(offset + 0xF711F7, 0x08);
		Process::Write8(offset + 0xF711F8, 0x09);
		Process::Write8(offset + 0xF711F9, 0x0A);
		Process::Write8(offset + 0xF711FA, 0x0B);
		Process::Write8(offset + 0xF711FB, 0x0C);
		Process::Write8(offset + 0xF711FC, 0x0D);
		Process::Write8(offset + 0xF711FD, 0x0E);
		Process::Write8(offset + 0xF711FE, 0x10);
		Process::Write8(offset + 0xF711FF, 0x11);
		Process::Write8(offset + 0xF71200, 0x12);
		Process::Write8(offset + 0xF71201, 0x13);
		Process::Write8(offset + 0xF71202, 0x14);
		Process::Write8(offset + 0xF71203, 0x15);
		Process::Write8(offset + 0xF71204, 0x16);
		Process::Write8(offset + 0xF71205, 0x17);
		Process::Write8(offset + 0xF71206, 0x18);
		Process::Write8(offset + 0xF71207, 0x19);
		Process::Write8(offset + 0xF71208, 0x1A);
		Process::Write8(offset + 0xF71209, 0x1B);
		Process::Write8(offset + 0xF7120A, 0x1C);
		Process::Write8(offset + 0xF7120B, 0x1D);
		Process::Write8(offset + 0xF7120C, 0x1E);
		Process::Write8(offset + 0xF7120D, 0x20);
		Process::Write8(offset + 0xF7120E, 0x21);
		Process::Write8(offset + 0xF7120F, 0x24);
		Process::Write8(offset + 0xF71210, 0x26);
		Process::Write8(offset + 0xF71211, 0x2C);
		Process::Write8(offset + 0xF71212, 0x28);
		Process::Write8(offset + 0xF71213, 0x2A);
		Process::Write8(offset + 0xF71214, 0x27);
		Process::Write8(offset + 0xF71215, 0x29);
		Process::Write8(offset + 0xF71216, 0x2B);
		Process::Write8(offset + 0xF71217, 0x2E);
		MessageBox("4Pのアクションを変更したよ")();
	}
}

void act13(MenuEntry *entry)
{
	Keyboard key("ネタ帳アクション変更\nネタ帳のスペシャルを特定のアクションに変更します。",{"カーニバル1","カーニバル2","カーニバル3","カーニバル4","ちっちゃくなる","飛び込む","戻す"});
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write16(offset + 0x94BB44, 0x01DB);
		MessageBox("変更完了")();
	}
	if ( r == 1 ) {
		Process::Write16(offset + 0x94BB44, 0x01DC);
		MessageBox("変更完了")();
	}
	if ( r == 2 ) {
		Process::Write16(offset + 0x94BB44, 0x01DD);
		MessageBox("変更完了")();
	}
	if ( r == 3 ) {
		Process::Write16(offset + 0x94BB44, 0x01DE);
		MessageBox("変更完了")();
	}
	if ( r == 4 ) {
		Process::Write16(offset + 0x94BB44, 0x01E1);
		MessageBox("変更完了")();
	}
	if ( r == 5 ) {
		Process::Write16(offset + 0x94BB44, 0x0037);
		MessageBox("変更完了")();
	}
	if ( r == 6 ) {
		Process::Write32(offset + 0x94BB44, 0x00240198);
		MessageBox("元に戻したよ")();
	}
}

void act14(MenuEntry *entry)
{
	Process::Write32(offset + 0x1ACB5C, 0x3F809A0B);
}

void act15(MenuEntry *entry)
{
	Process::Write32(offset + 0x2725AC, 0x00000000);
}

void act16(MenuEntry *entry)
{
	Process::Write32(offset + 0x9A04C, 0x37B274F4);
}

void act17(MenuEntry *entry)
{
	if (Controller::IsKeysPressed( A ))
	{
		offset = 0x33000000;
		Process::(offset + 0x99FE4, 0x00009200);
		OSD::Notify("Action jajan" << Color::Yellow << "ON!");
	}
}

void act18(MenuEntry *entry)
{
	if (Controller::IsKeysPressed( A ))
	{
		if (Process::Read32(offset + 0x0099F84, cmp32) && cmp32 == 0xFFFFFFFF)
		{
		Process::Write32(offset + 0x0099FE4, 0x324C6080);
		}
		Process::Write32(offset + 0x009A110, 0x324C6080);
	}
}

/////////////////////////////////////////////////////////////
//                         プレイヤー                        //
/////////////////////////////////////////////////////////////

void player1(MenuEntry *entry)
{
	if (Controller::IsKeysPressed( DPadRight + L ))
	{
		Process::Write32(offset + 0x0064EF0C, 0xEA000052);
		Process::Write32(offset + 0x0064F070, 0xEA000001);
		Process::Write32(offset + 0x0064F0E8, 0xEA000014);
		Process::Write32(offset + 0x0064F19C, 0xE1A00000);
		Process::Write32(offset + 0x0064F1B4, 0xE1A00000);
		Process::Write32(offset + 0x0064F1B8, 0xEA000026);
		OSD::Notify("Through wall " << Color::Yellow << "ON!");
	}
	if (Controller::IsKeysPressed( DPadLeft + L ))
	{
		Process::Write32(offset + 0x0064EEF4, 0xEA000094);
		Process::Write32(offset + 0x0064F1E4, 0xEA000065);
		Process::Write32(offset + 0x0064EF0C, 0x0A000052);
		Process::Write32(offset + 0x0064F070, 0x0A000001);
		Process::Write32(offset + 0x0064F0E8, 0xDA000014);
		Process::Write32(offset + 0x0064F19C, 0xED841A05);
		Process::Write32(offset + 0x0064F1B4, 0xED840A07);
		Process::Write32(offset + 0x0064F1B8, 0x0A000026);
		OSD::Notify("Through wall " << Color::Yellow << "OFF!");
	}
}

void player2(MenuEntry *entry)
{
	Process::Write32(offset + 0x659160, 0xEA000014);
	Process::Write32(offset + 0x6774DC, 0xEA00002D);
}

void player3(MenuEntry *entry)
{
	Keyboard key("ソパカの国籍を変更します",{"なし","日本","埼玉","特別区","連邦保護領","ソウル特別市","アメリカ","韓国","イタリア","フィンランド","バチカン市国","チワワ州","タパスコ州","イカ","パラ","ファルコン","ララ","ホホ"});
	int r = key.Open();
	if ( r == 0 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x00);
			Process::Write8(offset + 0x00055D3, 0x00);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 1 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x01);
			Process::Write8(offset + 0x00055D3, 0x00);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 2 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x01);
			Process::Write8(offset + 0x00055D3, 0x0D);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 3 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x0A);
			Process::Write8(offset + 0x00055D3, 0x02);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 4 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x34);
			Process::Write8(offset + 0x00055D3, 0x19);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 5 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x88);
			Process::Write8(offset + 0x00055D3, 0x02);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 6 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x31);
			Process::Write8(offset + 0x00055D3, 0x00);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 7 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x88);
			Process::Write8(offset + 0x00055D3, 0x00);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 8 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x53);
			Process::Write8(offset + 0x00055D3, 0x00);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 9 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x4C);
			Process::Write8(offset + 0x00055D3, 0x00);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 10 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0xB9);
			Process::Write8(offset + 0x00055D3, 0x00);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 11 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x24);
			Process::Write8(offset + 0x00055D3, 0x08);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 12 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x24);
			Process::Write8(offset + 0x00055D3, 0x1C);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 13 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x2A);
			Process::Write8(offset + 0x00055D3, 0x0D);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 14 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x2E);
			Process::Write8(offset + 0x00055D3, 0x08);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 15 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x34);
			Process::Write8(offset + 0x00055D3, 0x0C);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 16 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x34);
			Process::Write8(offset + 0x00055D3, 0x0E);
		}
		MessageBox("国籍を変更したよ")();
	}
	if ( r == 17 ) {
		if (Process::Read32(offset + 0x0AA914C, offset) && offset != 0x00000000)
		{
			Process::Read32(offset + 0x0AA914C, offset);
			Process::Write8(offset + 0x00055D2, 0x6A);
			Process::Write8(offset + 0x00055D3, 0x02);
		}
		MessageBox("国籍を変更したよ")();
	}
}

void player4(MenuEntry *entry)
{
	Process::Write32(offset + 0x991C58, 0x00200000);
}

void player5(MenuEntry *entry)
{
	if (Controller::IsKeysPressed( B + DPadRight )) {
		Process::Write32(offset + 0x064D324, 0xE3A00001);
		Process::Write32(offset + 0x076225C, 0xE3A00000);
		Process::Write32(offset + 0x0651C4C, 0xE1A00000);
		Process::Write32(offset + 0x0652028, 0xE3A00000);
		OSD::Notify("Swim anywhere " << Color::Yellow << "ON!");
	}
	if (Controller::IsKeysPressed( B + DPadLeft )) {
		Process::Write32(offset + 0x064D324, 0xE3A00000);
		Process::Write32(offset + 0x076225C, 0xE3A00001);
		Process::Write32(offset + 0x0651C4C, 0xEBFC62D8);
		Process::Write32(offset + 0x0652028, 0xEB00AFB7);
		OSD::Notify("Swim anywhere " << Color::Yellow << "OFF!");
	}
}

void player6(MenuEntry *entry)
{
	offset = 0x00000000;
	if (Controller::IsKeysPressed( X + DPadUp ))
	{
		Process::Write32(offset + 0x2FEC78, 0xE3A00001);
		OSD::Notify("Rewrite My Design " << Color::Yellow << "ON!");
	}
	if (Controller::IsKeysPressed( X + DPadDown ))
	{
		Process::Write32(offset + 0x2FEC78, 0xE3A00000);
		OSD::Notify("Rewrite My Design " << Color::Yellow << "OFF!");
	}
}

void player7(MenuEntry *entry)
{
	Process::Write32(offset + 0x650D80, 0xEA00002D);
}

void player8(MenuEntry *entry)
{
	offset = 0x00000000;
	if (Controller::IsKeysPressed( DPadUp ))
	{
		Process::Write32(offset + 0x6E63F4, 0xE3A01011);
	}
	if (Controller::IsKeysPressed( DPadDown ))
	{
		Process::Write32(offset + 0x6E63F4, 0xE3A0104C);
	}
}

void player9(MenuEntry *entry)
{
	offset = 0x00000000;
	if (Controller::IsKeysPressed( DPadUp ))
	{
		Process::Write32(offset + 0x6E63F4, 0xE3A01013);
	}
	if (Controller::IsKeysPressed( DPadDown ))
	{
		Process::Write32(offset + 0x6E63F4, 0xE3A0104C);
	}
}

void player10(MenuEntry *entry)
{
	offset = 0x00000000;
	if (Controller::IsKeysPressed( DPadUp ))
	{
		Process::Write32(offset + 0x6E63F4, 0xE3A01014);
	}
	if (Controller::IsKeysPressed( DPadDown ))
	{
		Process::Write32(offset + 0x6E63F4, 0xE3A0104C);
	}
}

void player11(MenuEntry *entry)
{
	offset = 0x00000000;
	if (Controller::IsKeysPressed( DPadUp ))
	{
		Process::Write32(offset + 0x6E63F4, 0xE3A0101B);
	}
	if (Controller::IsKeysPressed( DPadDown ))
	{
		Process::Write32(offset + 0x6E63F4, 0xE3A0104C);
	}
}

void player12(MenuEntry *entry)
{
	
	Keyboard key("住人(動物)の引越し\n住人の引越しフラグを立てます\n次の日には引越し完了",{"住人1","住人2","住人3","住人4","住人5","住人6","住人7","住人8","住人9","住人10",});
	int r = key.Open();
	
	if ( r == 0 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF751B4,0x0005B801);
		MessageBox("住人1引越し完了")();
	}
	if ( r == 1 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF776CC,0x0004B801);
		MessageBox("住人2引越し完了")();
	}
	if ( r == 2 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF79BE4,0x0004B801);
		MessageBox("住人3引越し完了")();
	}
	if ( r == 3 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF7C0FC,0x0004B801);
		MessageBox("住人4引越し完了")();
	}
	if ( r == 4 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF7E614,0x0004B801);
		MessageBox("住人5引越し完了")();
	}
	if ( r == 5 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF80B2C,0x0005B801);
		MessageBox("住人6引越し完了")();
	}
	if ( r == 6 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF83044,0x0005B801);
		MessageBox("住人7引越し完了")();
	}
	if ( r == 7 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF8555C,0x0005B801);
		MessageBox("住人8引越し完了")();
	}
	if ( r == 8 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF87A74,0x0005B801);
		MessageBox("住人9引越し完了")();
	}
	if ( r == 9 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF89F8C,0x0004B801);
		MessageBox("住人10引越し完了")();
	}
}

void player13(MenuEntry *entry)
{
	Keyboard key("住人(動物)の引越し解除\n住人の引越しフラグを消します\n次の日に引っ越さなくなる",{"住人1","住人2","住人3","住人4","住人5","住人6","住人7","住人8","住人9","住人10",});
	int r = key.Open();
	
	if ( r == 0 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF751B4,0x0005B800);
		MessageBox("住人1引越し解除完了")();
	}
	if ( r == 1 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF776CC,0x0004B800);
		MessageBox("住人2引越し解除完了")();
	}
	if ( r == 2 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF79BE4,0x0004B800);
		MessageBox("住人3引越し解除完了")();
	}
	if ( r == 3 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF7C0FC,0x0004B800);
		MessageBox("住人4引越し解除完了")();
	}
	if ( r == 4 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF7E614,0x0004B800);
		MessageBox("住人5引越し解除完了")();
	}
	if ( r == 5 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF80B2C,0x0005B800);
		MessageBox("住人6引越し解除完了")();
	}
	if ( r == 6 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF83044,0x0005B800);
		MessageBox("住人7引越し解除完了")();
	}
	if ( r == 7 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF8555C,0x0005B800);
		MessageBox("住人8引越し解除完了")();
	}
	if ( r == 8 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF87A74,0x0005B800);
		MessageBox("住人9引越し解除完了")();
	}
	if ( r == 9 ) {
		offset = 0x31000000;
		Process::Write32(offset + 0xF89F8C,0x0004B800);
		MessageBox("住人10引越し解除完了")();
	}
	
}

void player14(MenuEntry *entry)
{
	Keyboard key("歩くスピードを変更します\n通常 で元の速度に戻せます",{"通常","遅い","超遅い","速い","超速い"});
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x880B2C, 0x3F800000);
		Process::Write32(offset + 0x880B34, 0x3F800000);
		Process::Write32(offset + 0x880C04, 0x3F800000);
		MessageBox("速度: 通常")();
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x880B2C, 0x3F000000);
		Process::Write32(offset + 0x880B34, 0x3F000000);
		Process::Write32(offset + 0x880C04, 0x3F000000);
		MessageBox("速度: 遅い")();
	}
	if ( r == 2 ) {
		Process::Write32(offset + 0x880B2C, 0x3E000000);
		Process::Write32(offset + 0x880B34, 0x3E000000);
		Process::Write32(offset + 0x880C04, 0x3E000000);
		MessageBox("速度: 超遅い")();
	}
	if ( r == 3 ) {
		Process::Write32(offset + 0x880B2C, 0x3FF00000);
		Process::Write32(offset + 0x880B34, 0x3FF00000);
		Process::Write32(offset + 0x880C04, 0x3FF00000);
		MessageBox("速度: 速い")();
	}
	if ( r == 4 ) {
		Process::Write32(offset + 0x880B2C, 0x41000000);
		Process::Write32(offset + 0x880B34, 0x41000000);
		Process::Write32(offset + 0x880C04, 0x41000000);
		MessageBox("速度: 超速い")();
	}
}
	

/////////////////////////////////////////////////////////////
//                        写真館                           //
/////////////////////////////////////////////////////////////

void photo1(MenuEntry *entry)
	{
        if(Controller::IsKeysPressed( L + A ))
        {
            Sleep( Seconds(0.05) );
            File file;
            Directory dir( "jpg", true );
            Keyboard key( "ファイル名を入力してください" );
            key.SetMaxLength( 30 ); // 入力最大行
            std::string input;

            if( key.Open(input) != -1 )
            {
                if( input.find(".jpg") == std::string ::npos )
                {
                    input += ".jpg";
                }
                if( dir.OpenFile(file, input, File::RWC) == 0 )
                {
                    if( file.Dump(0x31F4F1D8, 0x1400) == 0 )
                    {
                        MessageBox( "File dumped to:\n" + file.GetFullName() )();
                    }
                    else
                    MessageBox( "エラー。", ".jpg作成失敗" )();
                }

                file.Flush();
                file.Close();
            }
        }
    }
	
void photo2(MenuEntry *entry)
    {
        if(Controller::IsKeysPressed( R + A ))
        {
            std::vector < std::string > FileList;
            Directory SavePDir;

            Directory::Open( SavePDir, "jpg", true );
            SavePDir.ListFiles( FileList, ".jpg" );
            Keyboard keyboard( "写真を選んでください。", FileList );
            int FileChoice = keyboard.Open();

            if( FileChoice < 0 )
                return;

            Sleep( Seconds(0.1f) );
            File SaveFile;
            SavePDir.OpenFile( SaveFile, FileList[FileChoice], File::READ );
            SaveFile.Inject( 0x31F4F1D8, 0x1400 );
            MessageBox( "変更しました。" )();
        }
    }
	
/////////////////////////////////////////////////////////////
//                          ベル                            //
/////////////////////////////////////////////////////////////
void money1(MenuEntry *entry)
{
	Process::Write32(offset + 0x2C01C8, 0xE3A08000);
}

	
/////////////////////////////////////////////////////////////
//                         スタイル                          //
/////////////////////////////////////////////////////////////

void style1(MenuEntry *entry)
{	
	 Keyboard key( "作成するファイルの名前を入力して下さい" );
            key.SetMaxLength( 8 ); // 入力最大行
            std::string input;

            if( key.Open(input) != -1 )
            {
				offset = 0x32000000;
				Process::Write8(offset + 0x184E0, 0x00);
            }
}

void style2(MenuEntry *entry)
{
	u8 value;
	std::string filename;
	Keyboard(filename).Open(value);
	offset = 0x32000000;
	Process::Write8(offset + 0x184E0, value);
}

void style3(MenuEntry *entry)
{
	u8 value;
	std::string filename;
	Keyboard(filename).Open(value);
	offset = 0x32000000;
	Process::Write8(offset + 0x184E1, value);
}


/////////////////////////////////////////////////////////////
//                         その他                           //
/////////////////////////////////////////////////////////////
void other1(MenuEntry *entry)
{
	Keyboard key("セーブメニューの表示設定をします",{"OFF","ON"});
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x1A08C8, 0xE1A00000);
		Process::Write32(offset + 0x1A08CC, 0xE3A00000);
		Process::Write32(offset + 0x1A08D0, 0xEB0E011D);
		MessageBox("セーブメニューをオフにしたよ")();
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x1A08C8, 0xE3A01040);
		Process::Write32(offset + 0x1A08CC, 0xE5900000);
		Process::Write32(offset + 0x1A08D0, 0xEB14CAC6);
		MessageBox("セーブメニューをオンにしたよ")();
	}
}

void other2(MenuEntry *entry)
{
	Keyboard key("スクリーンショットの設定をします",{"OFF","ON"});
	int r = key.Open();
	if ( r == 0 ) {
		Process::Write32(offset + 0x5B2AE0, 0xE3A00001);
		MessageBox("スクリーンショットをオフにしたよ")
	}
	if ( r == 1 ) {
		Process::Write32(offset + 0x5B2AE0, 0xE3500000);
		MessageBox("スクリーンショットをオフにしたよ")
	}
}

void other3(MenuEntry *entry)
{
	Process::Write32(offset + 0x568BF8, 0x7F7FFFFF);
}

void other4(MenuEntry *entry)
{
	offset = 0x31000000;
	Process::Write32(offset + 0xF4F1CC, 0xFF0000A8);
}

void other5(MenuEntry *entry)
{
	Process::Write32(offset + 0x6D12A0, 0xE3A00001);
}

void other6(MenuEntry *entry)
{
	offset = 0x32000000;
	Process::Write32(offset + 0xC99A10, 0x0211FFFF);
}

void other7(MenuEntry *entry)
{
	Process::Write32(offset + 0xAD0250, 0x01000000);
}


/////////////////////////////////////////////////////////////
//                         メンテ                            //
/////////////////////////////////////////////////////////////
void maintenance1(MenuEntry *entry)
{
	Keyboard key("ファイル、フォルダ等を管理する模擬システムです\n現在未完成のため動作で不具合を起こす可能性があります",{"txtファイル作成1","txtファイル作成2","txtファイル作成3"});
	int r = key.Open();
	if ( r == 0 ) {
		Sleep( Seconds(0.05) );
            File file;
            Directory dir( "txt", true );
            Keyboard key( "作成するファイルの名前を入力して下さい" );
            key.SetMaxLength( 30 ); // 入力最大行
            std::string input;

            if( key.Open(input) != -1 )
            {
                if( input.find(".txt") == std::string ::npos )
                {
                    input += ".txt";
                }
                if( dir.OpenFile(file, input, File::RWC) == 0 )
                {
                    if( file.Dump(0x00000001, 0x00) == 0 )
                    {
                        MessageBox( "作成しました\n" + file.GetFullName() )();
                    }
                    else
                    MessageBox( "作成しました\n/luma/plugins/0004000000086200/txt/ここ" )();
                }

                file.Flush();
                file.Close();
            }
	}
	if ( r == 1 ) {
		Sleep( Seconds(0.05) );
            File file;
            Directory dir( "txt", true );
            Keyboard key( "作成するファイルの名前を入力して下さい" );
            key.SetMaxLength( 30 ); // 入力最大行
            std::string input;

            if( key.Open(input) != -1 )
            {
                if( input.find(".txt") == std::string ::npos )
                {
                    input += ".txt";
                }
                if( dir.OpenFile(file, input, File::RWC) == 0 )
                {
                    if( file.Dump(0x31F4F1D8, 0x1400) == 0 )
                    {
                        MessageBox( "作成しました\n" + file.GetFullName() )();
                    }
                    else
                    MessageBox( "エラー", "作成失敗" )();
                }

                file.Flush();
                file.Close();
            }
	}
	if ( r == 2 ) {
		File::Create("../miku-test.txt");
		MessageBox( "作成しました\n")();
	}
	
}

void maintenance2(MenuEntry *entry)
{
	Keyboard key("3gxのファイル関連を管理します",{"color.bin無効化","color.binの確認","color.binを開く","color.binを読む","color.binが開かれているか確認","3gxのサイズを表示","3gxの配置確認","3gxの名前確認","3gxの拡張子確認"});
	int r = key.Open();
	if ( r == 0 ) {
		File::Rename("color.bin", "miku.txt");
	}
	if ( r == 1 ) {
		if(File::Exists("color.bin"))
		{
			MessageBox("color.binは正常です")();
		}
		else MessageBox("エラー","color.binを測定できませんでした")();
	}
	if ( r == 2 ) {
		File file;
		File::Open(file,"color.bin");//file.txtを開く
		file.Close();//file.txtを閉じる
	}
	if ( r == 3 ) {
		File file;
		u32 buf;
		File::Open(file,"color.bin");//file.binを開く
		file.Read((void*)&buf, sizeof(u32));//bufにfile.binの内容をu32のサイズ(4byte)分読み込む
		file.Close();//file.binを閉じる
	}
	if ( r == 4 ) {
		File file;
		File::Open(file,"color.bin");
		if(file.IsOpen())//ファイルがちゃんと開かれていたら
		OSD::Notify("File is Opening");
		file.Close();
	}
	if ( r == 5 ) {
		File file;
		File::Open(file,"UserCTRPF.3gx");
		u64 size = file.GetSize();//ファイルサイズを取得
		MessageBox("file size: " + file.GetSize())();
		file.Close();
	}
	if ( r == 6 ) {
		File file;
		File::Open(file,"UserCTRPF.3gx");
		std::string name = file.GetFullName();//"/luma/plugins/0004000000155100/file.bin"が返ってくる
		MessageBox("" + file.GetFullName())();
		file.Close();
	}
	if ( r == 7 ) {
		File file;
		File::Open(file,"UserCTRPF.3gx");
		std::string name = file.GetName();//"file.bin"が返ってくる
		MessageBox("" + file.GetName())();
		file.Close();
	}
	if ( r == 8 ) {
		File file;
		File::Open(file,"UserCTRPF.3gx");
		std::string ets = file.GetExtension();//"bin"が返ってくる
		MessageBox("" + file.GetExtension())();
		file.Close();
	}
}

void maintenance3(MenuEntry *entry)
{
	Keyboard key("記入、ダンプ系\n不具合多め",{"32.binに19194545記入","32.txtに野獣先輩と記入","dump.binに184E0の値をダンプ","dump.binにdumpした値を書き込む"});
	int r = key.Open();
	if ( r == 0 ) {
		File file;
		u32 data = 0x19194545;
		File::Create("32.bin");
		File::Open(file,"32.bin");//file.binを開く
		file.Write((void*)&data, sizeof(u32));//dataの内容をにfile.binに書き込む
		file.Flush();
		file.Close();//file.binを閉じる
	}
	if ( r == 1 ) {
		File file;
		File::Create("32.txt");
		File::Open(file,"32.txt");//file.txtを開く
		file.WriteLine("野獣先輩");//flle.txtに"Hello World!"と書き込まれる。
		file.Flush();
		file.Close();//file.txtを閉じる
	}
	if ( r == 2 ) {
		File file;
		File::Create("dump.bin");
		File::Open(file,"dump.bin");
		file.Dump(0x184E0,4);//0x100000のアドレスの値を4byte分ダンプ
		file.Flush(); //保存
		file.Close();
	}
	if ( r == 3 ) {
		//あらかじめ、file.binにバイナリデータ ff ff ff ffと書いておく
		File file;
		File::Open(file,"dunp.bin");
		file.Inject(0x184E0,4);//0x100000の値が0xffffffffになる
		file.Close();
	}
}

void maintenance4(MenuEntry *entry)
{
	Keyboard key("Utils関数",{"ランダムな値を送信します","0から10のランダムな値を送信します"});
	int r = key.Open();
	if ( r == 0 ) {
		MessageBox("" + Utils::Random(1, 2))();
	}
	if ( r == 1 ) {
		MessageBox("" + Utils::Random(0, 10))();
	}
}



//終わりの括弧↓
}
