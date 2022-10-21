#include <CTRPluginFramework.hpp>
#include "cheats.hpp"
#include "colorset.hpp"
#include "csvc.h"


namespace CTRPluginFramework
{
	
/*
	std::vector<std::string> colorNames = {	
											Color::White << "白色",				Color::Red << "赤色",
											Color::Lime << "黄緑色",				Color::Blue << "青色",			Color::Yellow << "黄色",
											Color::Cyan << "水色",				Color::Magenta << "紅紫色",		Color::Silver << "銀色",
											Color::Gray << "灰色",				Color::Maroon << "マルーン色",		Color::Olive << "オリーブ色",
											Color::Green << "緑色",				Color::Purple << "紫色",			Color::Teal << "青緑色",
											Color::Navy << "紺色",				Color::BlackGrey << "黒灰色",	Color::Brown << "茶色",
											Color::DarkGrey << "ダークグレー",		Color::DeepSkyBlue << "暗い水色",	Color::DimGrey << "暗い灰色",
											Color::DodgerBlue << "紺碧色",		Color::Gainsboro << "明るい灰色",	Color::ForestGreen << "深緑",
											Color::LimeGreen << "ライムグリーン",	Color::Orange << "橙色",			Color::SkyBlue << "水色",
											Color::Turquoise << "ターコイズ",
											};

	std::vector<Color> colors = {
									Color::White,		Color::Red,
									Color::Lime,		Color::Blue,		Color::Yellow,
									Color::Cyan,		Color::Magenta,		Color::Silver,
									Color::Gray,		Color::Maroon,		Color::Olive,
									Color::Green,		Color::Purple,		Color::Teal,
									Color::Navy,		Color::BlackGrey,	Color::Brown,
									Color::DarkGrey,	Color::DeepSkyBlue,	Color::DimGrey,
									Color::DodgerBlue,	Color::Gainsboro,	Color::ForestGreen,
									Color::LimeGreen,	Color::Orange,		Color::SkyBlue,
									Color::Turquoise,
								};

	void colorChange(int choose)
	{
		for(int i=0;i<colors.size();i++)
		{
			File::Remove(colorNames[i]);
		}
		File::Create(colorNames[choose]);
	}

	void menuColorsSelector(MenuEntry *e)
	{
		Keyboard kbd("",colorNames);
		int ch = kbd.Open();
		if(ch != -1)
			colorChange(ch);
	}

	Color getColor()
	{
		for(int i=0;i<colors.size();i++)
		{
			if(File::Exists(colorNames[i]))
				return colors[i];
		}
		return Color::White;
	}
*/


    // This function is called before main and before the game starts
    // Useful to do code edits safely
    void    PatchProcess(FwkSettings &settings)
    {

        if (File::Exists("color.bin")) {
            u8 red_value = 255;
            u8 green_value = 255;
            u8 blue_value = 255;
            File file;
            File::Open(file,"color.bin");
            file.Read((void*)&red_value, sizeof(u8));
            file.Seek(1);
            file.Read((void*)&green_value, sizeof(u8));
            file.Seek(1);
            file.Read((void*)&blue_value, sizeof(u8));
            file.Close();
            settings.BackgroundBorderColor = Color(red_value, green_value, blue_value);
        }
    }

    // This function is called when the process exits
    // Useful to save settings, undo patchs or clean up things
    void    OnProcessExit(void)
    {
		
    }
	
	const std::string NewLINE = "\n";//改行
	std::string CTRPFname = "とびだせどうぶつの森(製作版) JP";//3gx名前
	std::string about1 = "This 3gx was made by Taiyaki";//about1行目
	std::string about2 = "Secondary distribution strictly prohibited!";//about2行目
	std::string about3 = "Have fun with this 3gx!!";//about3行目
	std::string about4 = "YouTube : https://youtube.com/c/たいやき村長";//about4行目
	std::string about5 = "Twitter : https://twitter.com/TaiyakiSontyo";//about5行目
	static MenuEntry *AddArg(void *arg, MenuEntry *entry)
	{
		if (entry != nullptr)
			entry->SetArg(arg);
		return (entry);
	}

	static MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey& hotkey)
	{
		if (entry != nullptr)
		{
			entry->Hotkeys += hotkey;
			entry->SetArg(new std::string(entry->Name()));
			entry->Name() += " " + hotkey.ToString();
			entry->Hotkeys.OnHotkeyChangeCallback([](MenuEntry *entry, int index)
				{
					std::string *name = reinterpret_cast<std::string*>(entry->GetArg());

					entry->Name() = *name + " " + entry->Hotkeys[0].ToString();
				});
		}
		return (entry);
	}

	static MenuEntry *EntryWithHotkey(MenuEntry *entry, const std::vector<Hotkey>& hotkeys)
	{
		if (entry != nullptr)
		{
			for (const Hotkey& hotkey : hotkeys)
				entry->Hotkeys += hotkey;
		}
		return (entry);
	}

	static MenuEntry *EnabledEntry(MenuEntry *entry)
	{
		if (entry != nullptr) entry->Enable();
		return (entry);
	}

	PluginMenu *Pmenu;

	void InitMenu()	
	{
		
		MenuFolder *fa = new MenuFolder("クレジット");
			
			*fa += new MenuEntry(Color::Orange << "製作者", nullptr,setumei1);
			*fa += new MenuEntry(Color::Orange << "協力者",nullptr,setumei3);
		
		MenuFolder *fb = new MenuFolder(Color::Orange << "ON推奨");
		
			*fb += new MenuEntry(Color::Orange << "チートONTest",cheat6,"途中");
			*fb += new MenuEntry(Color::Orange << "チートON",cheat1,"文字突破\n改行など");
			*fb += new MenuEntry(Color::Orange << "花散らさない",cheat2,"走っても花を散らさない");
			*fb += new MenuEntry(Color::Orange << "相手通り抜けられる",nullptr,cheat3,"他の人を貫通できます");
			*fb += new MenuEntry(Color::Orange << "壁貫通",cheat4,"ON: L + →\nOFF: L + ←");
			*fb += new MenuEntry(Color::Orange << "穴に落ちなくなる",cheat5,"穴の上を歩ける");
			*fb += new MenuEntry(Color::Orange << "置き方変更",item5,"X+↓");

		MenuFolder *fd = new MenuFolder(Color::Orange << "アイテム/ポケット/ドロップ");
		
			MenuFolder *fd1 = new MenuFolder(Color::Orange << "アイテム");
				
				MenuFolder *fd1a = new MenuFolder(Color::Orange << "拾い方");
					*fd1a += new MenuEntry(Color::Orange << "なんでも拾う",nullptr,item1);
					*fd1a += new MenuEntry(Color::Orange << "アイテムをポケットにしまう",item11);
					*fd1a += new MenuEntry(Color::Orange << "ポケットいっぱい",item12);
					*fd1a += new MenuEntry(Color::Orange << "ポケット表示",item13);
					*fd1a += new MenuEntry(Color::Orange << "拾う途中",item14);
					*fd1a += new MenuEntry(Color::Orange << "拾う",item15);
					*fd1a += new MenuEntry(Color::Orange << "拾って見せる",item16);
					*fd1a += new MenuEntry(Color::Orange << "フライパン所持",item49,"Xで所持\nうまく機能しない場合があります\n\n提供: のむさん\nThank you!");
					*fd1a += new MenuEntry(Color::Orange << "フライパン表示",item50,"所持してるアイテムがフライパンになります\n\n提供: のむさん\nThank you!");
				fd1->Append(fd1a);
				
				MenuFolder *fd1b = new MenuFolder(Color::Orange << "木");
					*fd1b += new MenuEntry(Color::Orange << "木を一回で切れる",item2);
					*fd1b += new MenuEntry(Color::Orange << "木切れない",nullptr,item3);
				fd1->Append(fd1b);
				
				MenuFolder *fd1d = new MenuFolder(Color::Orange << "スコップ");
					*fd1d += new MenuEntry(Color::Orange << "穴を掘る動作//普通",item38);
					*fd1d += new MenuEntry(Color::Orange << "穴を掘る動作//切り株",item39);
					*fd1d += new MenuEntry(Color::Orange << "穴を掘る動作//掘る",item40);
					*fd1d += new MenuEntry(Color::Orange << "切り株を掘る動作//普通",item41);
					*fd1d += new MenuEntry(Color::Orange << "切り株を掘る動作//岩",item42);
					*fd1d += new MenuEntry(Color::Orange << "切り株を掘る動作//掘り出す",item43);
					*fd1d += new MenuEntry(Color::Orange << "切り株を掘る動作//埋める",item44);
					*fd1d += new MenuEntry(Color::Orange << "岩を壊す動作//普通",item45);
					*fd1d += new MenuEntry(Color::Orange << "岩を壊す動作//掘り出す",item46);
					*fd1d += new MenuEntry(Color::Orange << "岩を壊す動作//切り株",item47);
					*fd1d += new MenuEntry(Color::Orange << "岩を壊す動作//埋める",item48);
				fd1->Append(fd1d);
				
				MenuFolder *fd1c = new MenuFolder(Color::Orange << "その他");
					*fd1c += new MenuEntry(Color::Orange << "拾う速度上昇",item17,"拾うスピード上昇: ↑ + X + L\n捨てるスピード上昇: → + X + L\nクローバーで拾うスピード上昇: ↓ + X + L");
					*fd1c += new MenuEntry(Color::Orange << "アイテム速度上昇",nullptr,item18,"01: スコップで掘る\n02: 地面に埋める\n03: 掘り出す\n04: ジョウロ\n05: 網\n06: オノ跳ね返り");
					*fd1c += new MenuEntry(Color::Orange << "遊び道具速度上昇",nullptr,item19,"01: ピコピコハンマー\n02: 豆\n03: シャボン玉\n04: 風車\n05: 恵方巻,アイス\n06: コーヒー,サイダー\n07: クラッカー");
					*fd1c += new MenuEntry(Color::Orange << "アクション動作速度上昇",nullptr,item20,"01: ドアの開閉\n02: 直立呼吸\n03: エリア移動時の自動歩行\n04: 建物から出る\n05: 向きを変えて椅子から降りる\n06: 住人歩行速度\n07: プレイヤー歩行速度");
					*fd1c += new MenuEntry(Color::Orange << "何でもおいしく食べる",item27);
					*fd1c += new MenuEntry(Color::Orange << "ポケット項目追加",item34,"項目が'部屋に飾る,壁にかける,食べる,地面に植える,みせびらかす,飲む,タイマーを計る,おサイフにしまう'に変化します");
					*fd1c += new MenuEntry(Color::Orange << "ポケット項目消去",item35,"項目が'やめる'だけになります");
					*fd1c += new MenuEntry(Color::Orange << "道具機能変更",nullptr,item37);
				fd1->Append(fd1c);
				
			fd->Append(fd1);
			
			MenuFolder *fd2 = new MenuFolder(Color::Orange << "ポケット");
				*fd2 += new MenuEntry(Color::Orange << "ポケットからアイテム置いたときに捨てない",nullptr,item4);
				*fd2 += new MenuEntry(Color::Orange << "食べたり埋めたりしてもアイテムが消えない",nullptr,item36);
				*fd2 += new MenuEntry(Color::Orange << "ポケットのアイテム削除",nullptr,item21);
				*fd2 += new MenuEntry(Color::Orange << "グループでアイテムをセット(フルーツ)",nullptr,item22,"01: 無限フルーツ\n02: 無限おいしいフルーツ");
				*fd2 += new MenuEntry(Color::Orange << "グループでアイテムをセット(道具)",nullptr,item23,"01: 金道具\n02: 銀道具\n03: レンタル道具\n04: マリンスーツ");
				*fd2 += new MenuEntry(Color::Orange << "グループでアイテムをセット(サンリオ)",nullptr,item24,"01: ハローキティ\n02: シナモロール\n03: ポムポムプリン\n04: マイメロディ\n05: キキ&ララ\n06: けろけろけろっぴ");
				*fd2 += new MenuEntry(Color::Orange << "さきゅなりきりアイテムをセット",nullptr,item32,"さきゅちゃんねる！のさきゅのなりきりセットをポケットにセットします");
				*fd2 += new MenuEntry(Color::Orange << "花をポケットにセット",nullptr,item33,"01: バラ\n02: コスモス\n03: チューリップ\n04: パンジー\n05: カーネーション\n06: ユリ\n07: すみれ\n08: その他");
				*fd2 += new MenuEntry(Color::Orange << "キャンピングカーの注文をポケットに入れる",item25,"注文画面を上画面に表示した時、R+Yでポケットに追加");
				*fd2 += new MenuEntry(Color::Orange << "カタログの注文をポケットに入れる",item26,"カタログの画面を上画面に表示した時、R+Yでポケットに追加");
				*fd2 += new MenuEntry(Color::Orange << "ポケットに没アイテム表示",item28,"ポケットに???のアイテムを表示させます");
				*fd2 += new MenuEntry(Color::Orange << "拾った没アイテムがポケットに入る",item29,"何でも拾う　で拾ったアイテムをポケットに入れられる");
			fd->Append(fd2);
			
			MenuFolder *fd3 = new MenuFolder(Color::Orange << "ドロップ");
				*fd3 += new MenuEntry(Color::Orange << "ポケットのアイテムを動かして置く",nullptr,item6);
				*fd3 += new MenuEntry(Color::Orange << "誰の家でも置ける",item7);
				*fd3 += new MenuEntry(Color::Orange << "Auto Drop",nullptr,item8);
				*fd3 += new MenuEntry(Color::Orange << "置いた物透明",nullptr,item9);
				*fd3 += new MenuEntry(Color::Orange << "普通に置く",item10);
				*fd3 += new MenuEntry(Color::Orange << "スライド動作で置く",nullptr,item30);
				*fd3 += new MenuEntry(Color::Orange << "物を重ねて置ける",nullptr,item31);
			fd->Append(fd3);
			
			
		MenuFolder *fe = new MenuFolder(Color::Orange << "移動/アクション/島");
		
			MenuFolder *fe1 = new MenuFolder(Color::Orange << "移動");
				/**fe1 += new MenuEntry(Color::Orange << "タッチワープ",move7,"下画面のタッチしたところに移動します");*/
				*fe1 += new MenuEntry(Color::Orange << "座標移動＊未完成",move1,"asmコードc++にするのわけわからん");
				*fe1 += new MenuEntry(Color::Orange << "座標移動向き指定",move2,"座標移動と一緒び使うと、移動した方向に体が向くようになります");
				*fe1 += new MenuEntry(Color::Orange << "Bダッシュ速くなる",move3,"Bダッシュのスピードが速くなります");
				*fe1 += new MenuEntry(Color::Orange << "歩くスピード変更",nullptr,player14);
				*fe1 += new MenuEntry(Color::Orange << "部屋移動(地上)",nullptr,move4,"01: 村\n02: 駅\n03: キャンプ場\n04: 役場\n05: Rパーカーズ\n06: モダンな交番\n07: クラシックな交番\n08: カフェ\n09: リセット監視センター\n10: オートキャンプ(左)\n11: オートキャンプ(右)");
				*fe1 += new MenuEntry(Color::Orange << "通信中ワープ",nullptr,move5,"01: 島に全員ワープ\n02: 村に全員ワープ");
				*fe1 += new MenuEntry(Color::Orange << "プレイヤーテレポート",move6,"1P B＋↑\n2P B＋→\n3P B＋↓\n4P B＋←");
			fe->Append(fe1);
			
			MenuFolder *fe2 = new MenuFolder(Color::Orange << "アクション");
			
				MenuFolder *fe2a = new MenuFolder(Color::Orange << "オフライン限定アクション","提供:のむさん\nThank you!");
					*fe2a += new MenuEntry(Color::Orange << "カービィ",act14);
					*fe2a += new MenuEntry(Color::Orange << "顔消滅",act15);
					*fe2a += new MenuEntry(Color::Orange << "首が折れる",act16);
					*fe2a += new MenuEntry(Color::Orange << "じゃじゃーん",act17,"Aでリアクション");
				fe2->Append(fe2a);
				
				*fe2 += new MenuEntry(Color::Orange << "強制エラー",nullptr,act1);
				*fe2 += new MenuEntry(Color::Orange << "気絶",nullptr,act10);
				*fe2 += new MenuEntry(Color::Orange << "変な動き",act2,"自分にしか見えない");
				*fe2 += new MenuEntry(Color::Orange << "歩きながらリアクション",act3,"ししょーのリアクションを歩きながら使える");
				*fe2 += new MenuEntry(Color::Orange << "連続リアクション",act4,"X + R");
				*fe2 += new MenuEntry(Color::Orange << "アクション実行1",nullptr,act5,"Yで実行");
				*fe2 += new MenuEntry(Color::Orange << "アクション実行2",nullptr,act6,"Yで実行");
				*fe2 += new MenuEntry(Color::Orange << "アクション実行3",nullptr,act8,"外専用");
				*fe2 += new MenuEntry(Color::Orange << "アクション実行4",nullptr,act9,"常駐");
				*fe2 += new MenuEntry(Color::Orange << "ACTコマンド",nullptr,act7,"必要なのだけにまとめました");
				*fe2 += new MenuEntry(Color::Orange << "師匠のアクションコピー",nullptr,act12);
				*fe2 += new MenuEntry(Color::Orange << "ネタ帳アクション変更",nullptr,act13,"ネタ帳のスペシャルのアクションを変更します");
			fe->Append(fe2);


			MenuFolder *fc = new MenuFolder(Color::Orange << "島");
		
				MenuFolder *fc1 = new MenuFolder(Color::Orange << "ツアー");
					*fc1 += new MenuEntry(Color::Orange << "ツアーリセット",sima12,"ツアーをリセットします");
					*fc1 += new MenuEntry(Color::Orange << "ロボット浮遊",sima13,"ツアーのロボットがムーンジャンプ状態になります");
					*fc1 += new MenuEntry(Color::Orange << "ツアー強制終了",sima14,"ツアーを強制終了します");
					*fc1 += new MenuEntry(Color::Orange << "ツアー時間無制限",sima15,"ツアーの時間が無限になります");
				fc->Append(fc1);
			
				MenuFolder *fc2 = new MenuFolder(Color::Orange << "乗っ取り");
					*fc2 += new MenuEntry(Color::Orange << "乗っ取り", nullptr ,sima2);
					*fc2 += new MenuEntry(Color::Orange << "乗っ取るプレイヤー変更",nullptr,sima26,"乗っ取るプレイヤーを変更するよ");
					*fc2 += new MenuEntry(Color::Orange << "どこでも島乗っ取り",sima27);
					*fc2 += new MenuEntry(Color::Orange << "視点乗っ取り", nullptr,sima3);
					*fc2 += new MenuEntry(Color::Orange << "他の人を動かす",sima4);
					*fc2 += new MenuEntry(Color::Orange << "アクション乗っ取り", nullptr,sima5);
					*fc2 += new MenuEntry(Color::Orange << "チャット乗っ取り",sima21,"A+十字キー\n提供: のむさん\nThank you!");
					*fc2 += new MenuEntry(Color::Orange << "自分と同じ動作させる",nullptr,sima24);
					*fc2 += new MenuEntry(Color::Orange << "髪型乗っ取り",sima25,"回ると反映される");
				fc->Append(fc2);
			
				MenuFolder *fc3 = new MenuFolder(Color::Orange << "プレイヤー");
					*fc3 += new MenuEntry(Color::Orange << "プレイヤークラッシュ",nullptr,sima11);
					*fc3 += new MenuEntry(Color::Orange << "プレイヤー閉じ込め",nullptr,sima16);
					*fc3 += new MenuEntry(Color::Orange << "強制エラー",sima20,"L + X\n提供: のむさん\nThank you!");
					*fc3 += new MenuEntry(Color::Orange << "自分透明化",sima23,"自分の画面では透明になりません\n提供: のむさん\nThank you!");
					*fc3 += new MenuEntry(Color::Orange << "ムーンジャンプ",sima28,"オンライン対応\n\nL+↑: ON\nL+↓: OFF");
				fc->Append(fc3);
			
				MenuFolder *fc4 = new MenuFolder(Color::Orange << "その他");
					*fc4 += new MenuEntry(Color::Orange << "島にワープ",sima1,"使うと詰み状態になります");
					*fc4 += new MenuEntry(Color::Orange << "電気スイッチ追加",sima7,Color::Orange << "部屋の模様替えを押すとエラーになるから押さないでね！");
					*fc4 += new MenuEntry(Color::Orange << "島でフレンド申請追加",nullptr,sima8);
					*fc4 += new MenuEntry(Color::Orange << "島のアイテム無料",sima9,"島のアイテムが無料になるよ");
					*fc4 += new MenuEntry(Color::Orange << "引き取りボックス機能変更",sima10);
					*fc4 += new MenuEntry(Color::Orange << "チャット消えない",sima17,"ベスチャが使えなくなります\nチートONと併用ができません\n\n提供: のむさん\nThank you!");
					*fc4 += new MenuEntry(Color::Orange << "@マーク使用可能",sima18,"提供: のむさん\nThank you!");
					*fc4 += new MenuEntry(Color::Orange << "文字数制限解除(島)",sima19,"提供: のむさん\nThank you!");
					*fc4 += new MenuEntry(Color::Orange << "島のおみやげ変更",sima22,"オンライン対応\n全て売り切れになります\n提供: のむさん\nThank you!");
				fc->Append(fc4);
				
			fe->Append(fc);
			
			
			
		MenuFolder *ff = new MenuFolder(Color::Orange << "プレイヤー/住人(動物)");
			
			MenuFolder *ff1 = new MenuFolder(Color::Orange << "プレイヤー");
				*ff1 += new MenuEntry(Color::Orange << "壁貫通",player1,"ON: L + →\nOFF: L + ←");
				*ff1 += new MenuEntry(Color::Orange << "穴に落ちなくなる",player2,"穴の上を歩ける");
				*ff1 += new MenuEntry(Color::Orange << "国籍変更",nullptr,player3);
				*ff1 += new MenuEntry(Color::Orange << "他の人がいても家具を動かせる",player4,"他の人がいても家具を動かすことが出来ます");
				*ff1 += new MenuEntry(Color::Orange << "どこでも泳ぐ",player5,"B+→ ON\nB+← OFF");
				*ff1 += new MenuEntry(Color::Orange << "他人のマイデザを書き換える",player6,"X+↑ ON\nX+↓ OFF");
				*ff1 += new MenuEntry(Color::Orange << "通信中押されない",player7,"他の人から押されなくなります");
			ff->Append(ff1);
			
			MenuFolder *ff2 = new MenuFolder(Color::Orange << "住人");
				*ff2 += new MenuEntry(Color::Orange << "NPC着替えさせる",player8,"↑ ON\n↓ OFF");
				*ff2 += new MenuEntry(Color::Orange << "NPC着替えさせる(エフェクト無し)",player9,"↑ ON\n↓ OFF");
				*ff2 += new MenuEntry(Color::Orange << "NPCくるりんぱ",player10,"↑ ON\n↓ OFF");
				*ff2 += new MenuEntry(Color::Orange << "NPC消える",player11,"↑ ON\n↓ OFF");
				*ff2 += new MenuEntry(Color::Orange << "住人引越し",nullptr,player12,"日付を変更すると引越しします");
				*ff2 += new MenuEntry(Color::Orange << "住人引越し解除",nullptr,player13,"住人が引っ越さなくなります");
			ff->Append(ff2);
			
		MenuFolder *fg = new MenuFolder(Color::Orange << "公共事業/商店街/地形/写真館");
		
			MenuFolder *fg1 = new MenuFolder(Color::Orange << "公共事業");
			
			fg->Append(fg1);
			
			MenuFolder *fg2 = new MenuFolder(Color::Orange << "商店街");
			
			fg->Append(fg2);
			
			MenuFolder *fg3 = new MenuFolder(Color::Orange << "地形");
			
			fg->Append(fg3);
			
			MenuFolder *fg4 = new MenuFolder(Color::Orange << "写真館");
				*fg4 += new MenuEntry(Color::Orange << "現在のソパカの写真保存",photo1,"L+A");
				*fg4 += new MenuEntry(Color::Orange << "保存されているソパカの写真読み込み",photo2,"R+A");
			fg->Append(fg4);
			
			
			
		MenuFolder *fh = new MenuFolder(Color::Orange << "ベル/故郷チケット/島メダル/バッジ");
		
			MenuFolder *fh1 = new MenuFolder(Color::Orange << "ベル");
				*fh1 += new MenuEntry(Color::Orange << "所持金額固定",money1);
			fh->Append(fh1);
			
			MenuFolder *fh2 = new MenuFolder(Color::Orange << "故郷チケット");
			
			fh->Append(fh2);
			
			MenuFolder *fh3 = new MenuFolder(Color::Orange << "島メダル");
			
			fh->Append(fh3);
			
			MenuFolder *fh4 = new MenuFolder(Color::Orange << "バッジ");
			
			fh->Append(fh4);
			
			
			
		MenuFolder *fi = new MenuFolder(Color::Orange << "自分のスタイル/家のスタイル/リフォーム");
		
			MenuFolder *fi1 = new MenuFolder(Color::Orange << "自分のスタイル");
				*fi1 += new MenuEntry(Color::Orange << "髪型変更(男)",nullptr,style1,"各種説明から説明を見てね");
				*fi1 += new MenuEntry(Color::Orange << "髪型変更(女)",nullptr,style2,"各種説明から説明を見てね");
				*fi1 += new MenuEntry(Color::Orange << "髪の色変更",nullptr,style3,"各種説明から説明みてね");
		fi->Append(fi1);
			
			MenuFolder *fi2 = new MenuFolder(Color::Orange << "家のスタイル");
			
			fi->Append(fi2);
			
			MenuFolder *fi3 = new MenuFolder(Color::Orange << "リフォーム");
			
			fi->Append(fi3);
			
			
			
			
		MenuFolder *fj = new MenuFolder(Color::Orange << "その他");
			*fj += new MenuEntry(Color::Orange << "セーブメニュー表示",nullptr,other1);
			*fj += new MenuEntry(Color::Orange << "スクリーンショット",nullptr,other2);
			*fj += new MenuEntry(Color::Orange << "メニューの開閉速度上昇",other3);
			*fj += new MenuEntry(Color::Orange << "デバッグメニュー追加",other4,"ソパカの真ん中のところに追加されます");
			*fj += new MenuEntry(Color::Orange << "チャット見えない",other5);
			*fj += new MenuEntry(Color::Orange << "チャット欄消失",other6);
			*fj += new MenuEntry(Color::Orange << "改行ON",other7);
		
		
		MenuFolder *fk = new MenuFolder("メンテナンス");
			*fk += new MenuEntry(Color::Orange << "ファイル編集",nullptr,maintenance1);
			*fk += new MenuEntry(Color::Orange << "3gx関連ファイル編集",nullptr,maintenance2);
			*fk += new MenuEntry(Color::Orange << "ファイル記入系",nullptr,maintenance3);
			*fk += new MenuEntry(Color::Orange << "Utile系",nullptr,maintenance4);
		
		
		*Pmenu += new MenuEntry(Color::Orange << "各種説明",nullptr,setumei2);
		/*各種説明*/
		*Pmenu += fb;
		/*ON推奨*/
		*Pmenu += fd;
		/*アイテム/ポケット/ドロップ*/
		*Pmenu += fe;
		/*移動/アクション/島*/
		*Pmenu += ff;
		/*プレイヤー/住人(動物)*/
		*Pmenu += fg;
		/*公共事業/商店街/地形/写真館*/
		*Pmenu += fh;
		/*ベル/故郷チケット/島メダル/バッジ*/
		*Pmenu += fi;
		/*自分のスタイル/家のスタイル/リフォーム*/
		*Pmenu += fj;
		/*その他*/
		//*Pmenu += new MenuEntry(menuColor << "文字の色変更",nullptr,menuColorsSelector);
		//
		*Pmenu += new MenuEntry("Set Background Color", nullptr, set_background_border_color);
		/*Set Background Color*/
		*Pmenu += fk;
		/*メンテナンス*/
		*Pmenu += fa;
		/*クレジット*/
		

	}

	
	


	
	int main(void)
		
	{

		MessageBox("チート画面で下画面の'Tools'の中の'Settings'の中の'auto'の項目4点にチェックを入れると、設定したものとFavoriteを記憶します。\n他の3gxからの変更やバージョンの変更で動作がおかしい場合は" << Color::Yellow << " CTRPFDate.bin " << Color::White << "を削除して初期設定を行ってください\n\nなにかバグ等不具合があれば" << Color::Cyan << " たいやき#5374 " << Color::White << "まで。",DialogType::DialogOk).SetClear(ClearScreen::None)();
		
		Pmenu = new PluginMenu(Color::LimeGreen << CTRPFname, 0, 0, 9, about1 + NewLINE + about2 + NewLINE + about3 + NewLINE + about4 + NewLINE + about5);
		Pmenu->SynchronizeWithFrame(true);
		OSD::Notify(Color::Cyan << "Made by Taiyaki!");
		OSD::Notify(Color::Cyan << "Loading ACNL_PLG...");
		OSD::Notify(Color::Red << "P" << 
					Color::Lime << "l" << 
					Color::Blue << "u" <<
					Color::Yellow << "g" <<
					Color::Cyan << "i" << 
					Color::Magenta << "n " << 
					Color::Red << "R" <<
					Color::Green << "e" << 
					Color::Purple << "a" << 
					Color::SkyBlue << "d" << 
					Color::Orange << "y" << 
					Color::LimeGreen << "!");
		Pmenu->ShowWelcomeMessage(false);
		
		
		InitMenu();
		Pmenu->Run();
		delete Pmenu;
		return 0;
	}

}