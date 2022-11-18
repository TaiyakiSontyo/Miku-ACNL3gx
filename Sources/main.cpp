#include <CTRPluginFramework.hpp>
#include "3ds.h"
#include "cheats.hpp"
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
		
		if (File::Exists("color1.bin")) {
            u8 red_value = 255;
            u8 green_value = 255;
            u8 blue_value = 255;
            File file;
            File::Open(file,"color1.bin");
            file.Read((void*)&red_value, sizeof(u8));
            file.Seek(1);
            file.Read((void*)&green_value, sizeof(u8));
            file.Seek(1);
            file.Read((void*)&blue_value, sizeof(u8));
            file.Close();
            settings.BackgroundMainColor = Color(red_value, green_value, blue_value);
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
			
			*fa += new MenuEntry("製作者", nullptr,setumei1);
			*fa += new MenuEntry("協力者",nullptr,setumei3);
		
		MenuFolder *fb = new MenuFolder("ON推奨");
		
			*fb += new MenuEntry("チートONTest",cheat6,"途中");
			*fb += new MenuEntry("チートON",cheat1,"文字突破\n改行など");
			*fb += new MenuEntry("花散らさない",cheat2,"走っても花を散らさない");
			*fb += new MenuEntry("相手通り抜けられる",nullptr,cheat3,"他の人を貫通できます");
			*fb += new MenuEntry("壁貫通",cheat4,"ON: L + →\nOFF: L + ←");
			*fb += new MenuEntry("穴に落ちなくなる",cheat5,"穴の上を歩ける");
			*fb += new MenuEntry("置き方変更",item5,"X+↓");
			*fb += new MenuEntry("ドロップ関連",item62,"X+→");

		MenuFolder *fd = new MenuFolder("アイテム/ポケット/ドロップ");
		
			MenuFolder *fd1 = new MenuFolder("アイテム");
				
				MenuFolder *fd1a = new MenuFolder("拾い方");
					*fd1a += new MenuEntry("なんでも拾う",nullptr,item1);
					*fd1a += new MenuEntry("アイテムをポケットにしまう",item11);
					*fd1a += new MenuEntry("ポケットいっぱい",item12);
					*fd1a += new MenuEntry("ポケット表示",item13);
					*fd1a += new MenuEntry("拾う途中",item14);
					*fd1a += new MenuEntry("拾う",item15);
					*fd1a += new MenuEntry("拾って見せる",item16);
					*fd1a += new MenuEntry("フライパン所持",item49,"Xで所持\nうまく機能しない場合があります\n\n提供: のむさん\nThank you!");
					*fd1a += new MenuEntry("フライパン表示",item50,"所持してるアイテムがフライパンになります\n\n提供: のむさん\nThank you!");
				fd1->Append(fd1a);
				
				MenuFolder *fd1b = new MenuFolder("木");
					*fd1b += new MenuEntry("木を一回で切れる",item2);
					*fd1b += new MenuEntry("木切れない",nullptr,item3);
					*fd1b += new MenuEntry("木をゆすると切れる",item66);
					*fd1b += new MenuEntry("切るときに倒すエフェクト表示",item67);
					*fd1b += new MenuEntry("木の実無限",item68);
					*fd1b += new MenuEntry("桜満開",nullptr,item69);
					*fd1b += new MenuEntry("クリスマスツリー",nullptr,item70);
				fd1->Append(fd1b);
				
				MenuFolder *fd1d = new MenuFolder("スコップ");
					*fd1d += new MenuEntry("穴を掘る動作//普通",item38);
					*fd1d += new MenuEntry("穴を掘る動作//切り株",item39);
					*fd1d += new MenuEntry("穴を掘る動作//掘る",item40);
					*fd1d += new MenuEntry("切り株を掘る動作//普通",item41);
					*fd1d += new MenuEntry("切り株を掘る動作//岩",item42);
					*fd1d += new MenuEntry("切り株を掘る動作//掘り出す",item43);
					*fd1d += new MenuEntry("切り株を掘る動作//埋める",item44);
					*fd1d += new MenuEntry("岩を壊す動作//普通",item45);
					*fd1d += new MenuEntry("岩を壊す動作//掘り出す",item46);
					*fd1d += new MenuEntry("岩を壊す動作//切り株",item47);
					*fd1d += new MenuEntry("岩を壊す動作//埋める",item48);
					*fd1d += new MenuEntry("掘り出したアイテム変更",item55,"掘り出したアイテムがお金になります");
					*fd1d += new MenuEntry("木,マイデザを掘れる",item63,"A長押しで掘れます");
					*fd1d += new MenuEntry("堀るときのアイテム変更",nullptr,item61);
					*fd1d += new MenuEntry("どこでも穴掘れる",nullptr,item64);
				fd1->Append(fd1d);
				
				MenuFolder *fd1c = new MenuFolder("その他");
					*fd1c += new MenuEntry("拾う速度上昇",item17,"拾うスピード上昇: ↑ + X + L\n捨てるスピード上昇: → + X + L\nクローバーで拾うスピード上昇: ↓ + X + L");
					*fd1c += new MenuEntry("アイテム速度上昇",nullptr,item18,"01: スコップで掘る\n02: 地面に埋める\n03: 掘り出す\n04: ジョウロ\n05: 網\n06: オノ跳ね返り");
					*fd1c += new MenuEntry("遊び道具速度上昇",nullptr,item19,"01: ピコピコハンマー\n02: 豆\n03: シャボン玉\n04: 風車\n05: 恵方巻,アイス\n06: コーヒー,サイダー\n07: クラッカー");
					*fd1c += new MenuEntry("アクション動作速度上昇",nullptr,item20,"01: ドアの開閉\n02: 直立呼吸\n03: エリア移動時の自動歩行\n04: 建物から出る\n05: 向きを変えて椅子から降りる\n06: 住人歩行速度\n07: プレイヤー歩行速度");
					*fd1c += new MenuEntry("何でもおいしく食べる",item27);
					*fd1c += new MenuEntry("食べるときの動作変更",nullptr,item57);
					*fd1c += new MenuEntry("ポケット項目追加",item34,"項目が'部屋に飾る,壁にかける,食べる,地面に植える,みせびらかす,飲む,タイマーを計る,おサイフにしまう'に変化します");
					*fd1c += new MenuEntry("ポケット項目消去",item35,"項目が'やめる'だけになります");
					*fd1c += new MenuEntry("ポケット項目追加(選択)",nullptr,item58);
					*fd1c += new MenuEntry("ポケット項目追加2(選択)",nullptr,item59);
					*fd1c += new MenuEntry("道具機能変更",nullptr,item37);
					*fd1c += new MenuEntry("どこでも釣りができる",nullptr,item65);
				fd1->Append(fd1c);
				
			fd->Append(fd1);
			
			MenuFolder *fd2 = new MenuFolder("ポケット");
				*fd2 += new MenuEntry("ポケットからアイテム置いたときに捨てない",nullptr,item4);
				*fd2 += new MenuEntry("食べたり埋めたりしてもアイテムが消えない",nullptr,item36);
				*fd2 += new MenuEntry("ポケットのアイテム削除",nullptr,item21);
				*fd2 += new MenuEntry("グループでアイテムをセット(フルーツ)",nullptr,item22,"01: 無限フルーツ\n02: 無限おいしいフルーツ");
				*fd2 += new MenuEntry("グループでアイテムをセット(道具)",nullptr,item23,"01: 金道具\n02: 銀道具\n03: レンタル道具\n04: マリンスーツ");
				*fd2 += new MenuEntry("グループでアイテムをセット(サンリオ)",nullptr,item24,"01: ハローキティ\n02: シナモロール\n03: ポムポムプリン\n04: マイメロディ\n05: キキ&ララ\n06: けろけろけろっぴ");
				*fd2 += new MenuEntry("さきゅなりきりアイテムをセット",nullptr,item32,"さきゅちゃんねる！のさきゅのなりきりセットをポケットにセットします");
				*fd2 += new MenuEntry("花をポケットにセット",nullptr,item33,"01: バラ\n02: コスモス\n03: チューリップ\n04: パンジー\n05: カーネーション\n06: ユリ\n07: すみれ\n08: その他");
				*fd2 += new MenuEntry("キャンピングカーの注文をポケットに入れる",item25,"注文画面を上画面に表示した時、R+Yでポケットに追加");
				*fd2 += new MenuEntry("カタログの注文をポケットに入れる",item26,"カタログの画面を上画面に表示した時、R+Yでポケットに追加");
				*fd2 += new MenuEntry("ポケットに没アイテム表示",item28,"ポケットに???のアイテムを表示させます");
				*fd2 += new MenuEntry("拾った没アイテムがポケットに入る",item29,"何でも拾う　で拾ったアイテムをポケットに入れられる");
				*fd2 += new MenuEntry("アイテム制限解除",nullptr,item51);
			fd->Append(fd2);
			
			MenuFolder *fd3 = new MenuFolder("ドロップ");
				*fd3 += new MenuEntry("ポケットのアイテムを動かして置く",nullptr,item6);
				*fd3 += new MenuEntry("誰の家でも置ける",item7);
				*fd3 += new MenuEntry("Auto Drop",nullptr,item8);
				*fd3 += new MenuEntry("置いた物透明",nullptr,item9);
				*fd3 += new MenuEntry("普通に置く",item10);
				*fd3 += new MenuEntry("スライド動作で置く",nullptr,item30);
				*fd3 += new MenuEntry("物を重ねて置ける",nullptr,item31);
				*fd3 += new MenuEntry("回転してドロップ",item52,"回転するとドロップします\nB+↑: ON\nB+↓: OFF");
				*fd3 += new MenuEntry("掘る動作でドロップ",item60);
				*fd3 += new MenuEntry("Aを押して地面のアイテムを消す",item53,"Aを押してね");
				*fd3 += new MenuEntry("置き花火燃えカス変更",nullptr,item54);
				*fd3 += new MenuEntry("置けない時の警告非表示",item56,"アイテムを置けないときの警告を無表示にします");
			fd->Append(fd3);
			
			
		MenuFolder *fe = new MenuFolder("移動/アクション/島");
		
			MenuFolder *fe1 = new MenuFolder("移動");
				/**fe1 += new MenuEntry("タッチワープ",move7,"下画面のタッチしたところに移動します");*/
				*fe1 += new MenuEntry("座標移動",move1,"十字キー + A");
				*fe1 += new MenuEntry("座標移動2",move9,"スライドパッド + R");
				*fe1 += new MenuEntry("座標移動向き指定",move2,"座標移動と一緒び使うと、移動した方向に体が向くようになります");
				*fe1 += new MenuEntry("Bダッシュ速くなる",move3,"Bダッシュのスピードが速くなります");
				*fe1 += new MenuEntry("歩くスピード変更",nullptr,player14);
				*fe1 += new MenuEntry("部屋移動(地上)",nullptr,move4,"01: 村\n02: 駅\n03: キャンプ場\n04: 役場\n05: Rパーカーズ\n06: モダンな交番\n07: クラシックな交番\n08: カフェ\n09: リセット監視センター\n10: オートキャンプ(左)\n11: オートキャンプ(右)");
				*fe1 += new MenuEntry("通信中ワープ",nullptr,move5,"01: 島に全員ワープ\n02: 村に全員ワープ");
				*fe1 += new MenuEntry("プレイヤーテレポート",move6,"1P B＋↑\n2P B＋→\n3P B＋↓\n4P B＋←");
				*fe1 += new MenuEntry("スライドパッドだけでダッシュ",nullptr,move8);
			fe->Append(fe1);
			
			MenuFolder *fe2 = new MenuFolder("アクション");
			
				MenuFolder *fe2a = new MenuFolder("オフライン限定アクション","提供:のむさん\nThank you!");
					*fe2a += new MenuEntry("カービィ",act14);
					*fe2a += new MenuEntry("顔消滅",act15);
					*fe2a += new MenuEntry("首が折れる",act16);
					*fe2a += new MenuEntry("じゃじゃーん",act17,"Aでリアクション");
				fe2->Append(fe2a);
				
				*fe2 += new MenuEntry("強制エラー",nullptr,act1);
				*fe2 += new MenuEntry("気絶",nullptr,act10);
				*fe2 += new MenuEntry("変な動き",act2,"自分にしか見えない");
				*fe2 += new MenuEntry("歩きながらリアクション",act3,"ししょーのリアクションを歩きながら使える");
				*fe2 += new MenuEntry("連続リアクション",act4,"X + R");
				*fe2 += new MenuEntry("リアクション固定/終了",act19,"Rで固定,Bで終了");
				*fe2 += new MenuEntry("動きが変になる",act23,"B+→:オン\nB+←:オフ");
				*fe2 += new MenuEntry("アクション実行1",nullptr,act5,"Yで実行");
				*fe2 += new MenuEntry("アクション実行2",nullptr,act6,"Yで実行");
				*fe2 += new MenuEntry("アクション実行3",nullptr,act8,"外専用");
				*fe2 += new MenuEntry("アクション実行4",nullptr,act9,"常駐");
				*fe2 += new MenuEntry("ACTコマンド",nullptr,act7,"必要なのだけにまとめました");
				*fe2 += new MenuEntry("師匠のアクションコピー",nullptr,act12);
				*fe2 += new MenuEntry("ネタ帳アクション変更",nullptr,act13,"ネタ帳のスペシャルのアクションを変更します");
				*fe2 += new MenuEntry("潜ると黒くなる",act18,"潜ると黒くなります");
				*fe2 += new MenuEntry("穴に落ちる",act20,"Rで穴に落ちます");
				*fe2 += new MenuEntry("自動歩行",act21,"Rで勝手に歩き出します");
				*fe2 += new MenuEntry("透明道具を持つ",act22,"道具を持っている上体になります");
				*fe2 += new MenuEntry("早着替え",act24,"Rで実行");
				*fe2 += new MenuEntry("即解除",nullptr,act25);
			fe->Append(fe2);


			MenuFolder *fc = new MenuFolder("島");
		
				MenuFolder *fc1 = new MenuFolder("ツアー");
					*fc1 += new MenuEntry("ツアーリセット",sima12,"ツアーをリセットします");
					*fc1 += new MenuEntry("ロボット浮遊",sima13,"ツアーのロボットがムーンジャンプ状態になります");
					*fc1 += new MenuEntry("ツアー強制終了",sima14,"ツアーを強制終了します");
					*fc1 += new MenuEntry("ツアー時間無制限",sima15,"ツアーの時間が無限になります");
				fc->Append(fc1);
			
				MenuFolder *fc2 = new MenuFolder("乗っ取り");
					*fc2 += new MenuEntry("乗っ取り", nullptr ,sima2);
					*fc2 += new MenuEntry("乗っ取るプレイヤー変更",nullptr,sima26,"乗っ取るプレイヤーを変更するよ");
					*fc2 += new MenuEntry("どこでも島乗っ取り",sima27);
					*fc2 += new MenuEntry("視点乗っ取り", nullptr,sima3);
					*fc2 += new MenuEntry("他の人を動かす",sima4);
					*fc2 += new MenuEntry("アクション乗っ取り", nullptr,sima5);
					*fc2 += new MenuEntry("チャット乗っ取り",sima21,"A+十字キー\n提供: のむさん\nThank you!");
					*fc2 += new MenuEntry("自分と同じ動作させる",nullptr,sima24);
					*fc2 += new MenuEntry("髪型乗っ取り",sima25,"回ると反映される");
				fc->Append(fc2);
			
				MenuFolder *fc3 = new MenuFolder("プレイヤー");
					*fc3 += new MenuEntry("プレイヤークラッシュ",nullptr,sima11);
					*fc3 += new MenuEntry("プレイヤー閉じ込め",nullptr,sima16);
					*fc3 += new MenuEntry("強制エラー",sima20,"L + X\n提供: のむさん\nThank you!");
					*fc3 += new MenuEntry("自分透明化",sima23,"自分の画面では透明になりません\n提供: のむさん\nThank you!");
					*fc3 += new MenuEntry("ムーンジャンプ",sima28,"オンライン対応\n\nL+↑: ON\nL+↓: OFF");
					*fc3 += new MenuEntry("P1判定",nullptr,sima34);
				fc->Append(fc3);
			
				MenuFolder *fc4 = new MenuFolder("その他");
					*fc4 += new MenuEntry("島にワープ",sima1,"使うと詰み状態になります");
					*fc4 += new MenuEntry("電気スイッチ追加",sima7,"部屋の模様替えを押すとエラーになるから押さないでね！");
					*fc4 += new MenuEntry("島でフレンド申請追加",nullptr,sima8);
					*fc4 += new MenuEntry("島のアイテム無料",sima9,"島のアイテムが無料になるよ");
					*fc4 += new MenuEntry("引き取りボックス機能変更",sima10);
					*fc4 += new MenuEntry("チャット消えない",sima17,"ベスチャが使えなくなります\nチートONと併用ができません\n\n提供: のむさん\nThank you!");
					*fc4 += new MenuEntry("@マーク使用可能",sima18,"提供: のむさん\nThank you!");
					*fc4 += new MenuEntry("文字数制限解除(島)",sima19,"提供: のむさん\nThank you!");
					*fc4 += new MenuEntry("3文字以上の数字使用可能",sima33);
					*fc4 += new MenuEntry("島のおみやげ変更",sima22,"オンライン対応\n全て売り切れになります\n提供: のむさん\nThank you!");
					*fc4 += new MenuEntry("ハニワのレンタルアイテム変更",sima35,"全て金道具になります");
				fc->Append(fc4);
				
				MenuFolder *fc5 = new MenuFolder("オフライン");
					*fc5 += new MenuEntry("ATMを売り切れ看板に変更",sima29);
					*fc5 += new MenuEntry("島のアイテム全消去",nullptr,sima30);
					*fc5 += new MenuEntry("全アイテムに水やり",nullptr,sima31);
					*fc5 += new MenuEntry("ハニワ変更",nullptr,sima32);
				fc->Append(fc5);
				
			fe->Append(fc);
			
			
			
		MenuFolder *ff = new MenuFolder("プレイヤー/住人(動物)");
			
			MenuFolder *ff1 = new MenuFolder("プレイヤー");
				*ff1 += new MenuEntry("壁貫通",player1,"ON: L + →\nOFF: L + ←");
				*ff1 += new MenuEntry("穴に落ちなくなる",player2,"穴の上を歩ける");
				*ff1 += new MenuEntry("国籍変更",nullptr,player3);
				*ff1 += new MenuEntry("他の人がいても家具を動かせる",player4,"他の人がいても家具を動かすことが出来ます");
				*ff1 += new MenuEntry("どこでも泳ぐ",player5,"B+→ ON\nB+← OFF");
				*ff1 += new MenuEntry("他人のマイデザを書き換える",player6,"X+↑ ON\nX+↓ OFF");
				*ff1 += new MenuEntry("通信中押されない",player7,"他の人から押されなくなります");
				*ff1 += new MenuEntry("アクセと同時に被り物を被れる",player15);
				*ff1 += new MenuEntry("海で歩ける",nullptr,player16);
				*ff1 += new MenuEntry("スライディング無効",nullptr,player17);
				*ff1 += new MenuEntry("住人と距離をとる",nullptr,player18);
				*ff1 += new MenuEntry("プレイヤー変更", nullptr, player19);
				*ff1 += new MenuEntry("プレイヤーの名前変更", nullptr, player20);
				*ff1 += new MenuEntry("プレイヤーの性別変更", nullptr, player21);
				*ff1 += new MenuEntry("プレイヤー変更",nullptr,player22,"途中でエラーになる場合があります\nまた、べスフレが引き継がれます");
			ff->Append(ff1);
			
			MenuFolder *ff2 = new MenuFolder("住人");
				*ff2 += new MenuEntry("NPC着替えさせる",player8,"↑ ON\n↓ OFF");
				*ff2 += new MenuEntry("NPC着替えさせる(エフェクト無し)",player9,"↑ ON\n↓ OFF");
				*ff2 += new MenuEntry("NPCくるりんぱ",player10,"↑ ON\n↓ OFF");
				*ff2 += new MenuEntry("NPC消える",player11,"↑ ON\n↓ OFF");
				*ff2 += new MenuEntry("住人引越し",nullptr,player12,"日付を変更すると引越しします");
				*ff2 += new MenuEntry("住人引越し解除",nullptr,player13,"住人が引っ越さなくなります");
			ff->Append(ff2);
			
		MenuFolder *fg = new MenuFolder("公共事業/商店街/地形/写真館");
		
			MenuFolder *fg1 = new MenuFolder("公共事業");
			
			fg->Append(fg1);
			
			MenuFolder *fg2 = new MenuFolder("商店街");
				*fg2 += new MenuEntry("夢番地公開設定",nullptr,yumemi1);
			fg->Append(fg2);
			
			MenuFolder *fg3 = new MenuFolder("地形");
			
			fg->Append(fg3);
			
			MenuFolder *fg4 = new MenuFolder("写真館");
				*fg4 += new MenuEntry("現在のソパカの写真保存",photo1,"L+A");
				*fg4 += new MenuEntry("保存されているソパカの写真読み込み",photo2,"R+A");
			fg->Append(fg4);
			
			
			
		MenuFolder *fh = new MenuFolder("ベル/故郷チケット/島メダル/バッジ");
		
			MenuFolder *fh1 = new MenuFolder("ベル");
				*fh1 += new MenuEntry("所持金額固定",money1);
				*fh1 += new MenuEntry("所持金変更",nullptr,money5);
				*fh1 += new MenuEntry("貯金最大",money2);
			fh->Append(fh1);
			
			MenuFolder *fh2 = new MenuFolder("故郷チケット");
				*fh2 += new MenuEntry("故郷チケット最大",money3);
			fh->Append(fh2);
			
			MenuFolder *fh3 = new MenuFolder("島メダル");
				*fh3 += new MenuEntry("島メダル最大",money4);
			fh->Append(fh3);
			
			MenuFolder *fh4 = new MenuFolder("バッジ");
				*fh4 += new MenuEntry("バッジ変更",nullptr,player23);
				*fh4 += new MenuEntry("オリジナル1",player24);
				*fh4 += new MenuEntry("オリジナル2",player25);
				*fh4 += new MenuEntry("オリジナル3",player26);
				*fh4 += new MenuEntry("オリジナル4",player27);
				*fh4 += new MenuEntry("オリジナル5",player28);
				*fh4 += new MenuEntry("オリジナル6",player29);
				*fh4 += new MenuEntry("オリジナル7",player30);
				*fh4 += new MenuEntry("カスタム金",player31);
				*fh4 += new MenuEntry("カスタム銀",player32);
				*fh4 += new MenuEntry("カスタム銅",player33);
				*fh4 += new MenuEntry("金の手紙",player34);
				*fh4 += new MenuEntry("風船",player35);
				*fh4 += new MenuEntry("大富豪",player36);
				*fh4 += new MenuEntry("銅釣",player37);
				*fh4 += new MenuEntry("金カタログマニア",player38);
				*fh4 += new MenuEntry("コンシェルジュ",player39);
				*fh4 += new MenuEntry("スペーストラベラー",player40);
				*fh4 += new MenuEntry("永遠のドリーマー",player41);
			fh->Append(fh4);
			
			
			
		MenuFolder *fi = new MenuFolder("自分のスタイル/家のスタイル/リフォーム");
		
			MenuFolder *fi1 = new MenuFolder("自分のスタイル");
				*fi1 += new MenuEntry("髪型変更(男)",nullptr,style1,"各種説明から説明を見てね");
				*fi1 += new MenuEntry("髪型変更(女)",nullptr,style2,"各種説明から説明を見てね");
				*fi1 += new MenuEntry("髪の色変更",nullptr,style3,"各種説明から説明みてね");
				*fi1 += new MenuEntry("目の色変更",nullptr,style4,"書く説明から説明みてね");
				*fi1 += new MenuEntry("目の形変更",nullptr,style5,"Bより大きい値を入力するとバグるよ！");
				*fi1 += new MenuEntry("日焼け度変更",nullptr,style6,"Eより大きい値を入力するとバグるよ！\n0が一番白に近く、Eが一番茶色に近くなります");
				*fi1 += new MenuEntry("誕生日変更",nullptr,player42);
				*fi1 += new MenuEntry("登録日変更",nullptr,player43);
		fi->Append(fi1);
			
			MenuFolder *fi2 = new MenuFolder("家のスタイル");
				*fi2 += new MenuEntry("家の大きさ変更",nullptr,house1);
				*fi2 += new MenuEntry("家の見た目変更",nullptr,house2);
				*fi2 += new MenuEntry("ドアの形変更",nullptr,house3);
				*fi2 += new MenuEntry("ドアの見た目変更",nullptr,house4);
			fi->Append(fi2);
			
			MenuFolder *fi3 = new MenuFolder("リフォーム");
			
			fi->Append(fi3);
			
			
			
			
		MenuFolder *fj = new MenuFolder("その他");
			MenuFolder *fj1 = new MenuFolder("音声");
				*fj1 += new MenuEntry("音楽を再生",nullptr,music35,"自分で好きなidを入力して流せます");
				*fj1 += new MenuEntry("音声ガイド",other18,"音声ガイドがオンになります");
				MenuFolder *fj1a = new MenuFolder("効果音");
					*fj1a += new MenuEntry("効果音を有効にする",music1,"L+↑:ON,L+↓:OFF,A:実行,R:stop\n\n効果音を有効にする前にONにしておいて下さい");
					*fj1a += new MenuEntry("コインを置く音",music2);
					*fj1a += new MenuEntry("お金を置く音",music3);
					*fj1a += new MenuEntry("ぴこ",music4);
					*fj1a += new MenuEntry("すぽ",music5);
					*fj1a += new MenuEntry("達成",music6);
					*fj1a += new MenuEntry("クラクション",music7);
					*fj1a += new MenuEntry("キラーン",music8);
					*fj1a += new MenuEntry("雷",music9);
					*fj1a += new MenuEntry("スタート",music10);
					*fj1a += new MenuEntry("唸り声",music11);
					*fj1a += new MenuEntry("にゃお",music12);
					*fj1a += new MenuEntry("ぽよ",music13);
				fj1->Append(fj1a);
				MenuFolder *fj1b = new MenuFolder("BGM");
					*fj1b += new MenuEntry("タイトル",music25);
					*fj1b += new MenuEntry("しずえ画面",music26);
					*fj1b += new MenuEntry("ハッピーホームアカデミー",music27);
					*fj1b += new MenuEntry("プレイヤー村に到着",music28);
					*fj1b += new MenuEntry("役場に向かえ",music29);
					*fj1b += new MenuEntry("家の場所決め",music30);
					*fj1b += new MenuEntry("家をここに決定",music31);
					*fj1b += new MenuEntry("新村長誕生",music32);
					*fj1b += new MenuEntry("午後",music33);
					*fj1b += new MenuEntry("けけアイドル",music34);
					*fj1b += new MenuEntry("没1",music14);
					*fj1b += new MenuEntry("没2",music15);
					*fj1b += new MenuEntry("没3",music16);
					*fj1b += new MenuEntry("没4",music17);
					*fj1b += new MenuEntry("没5",music18);
					*fj1b += new MenuEntry("没6",music19);
				fj1->Append(fj1b);
				MenuFolder *fj1c = new MenuFolder("ショートミュージック");
					*fj1c += new MenuEntry("1UP",music20);
					*fj1c += new MenuEntry("なんか起動する",music21);
					*fj1c += new MenuEntry("ピッピッ",music22);
					*fj1c += new MenuEntry("機械音",music23);
					*fj1c += new MenuEntry("ピロピロ",music24);
				fj1->Append(fj1c);
			fj->Append(fj1);
			MenuFolder *fj2 = new MenuFolder("常駐ON");
				*fj2 += new MenuEntry("セーブメニュー表示",nullptr,other1);
				*fj2 += new MenuEntry("スクリーンショット",nullptr,other2);
				*fj2 += new MenuEntry("ゲーム速度上昇", nullptr, other12);
				*fj2 += new MenuEntry("スピードハック",nullptr,other24);
				*fj2 += new MenuEntry("天気変更", nullptr, other13);
				*fj2 += new MenuEntry("ゲームモード変更",nullptr,other21);
				*fj2 += new MenuEntry("誰かが来た時のウィンドウ表示",nullptr,other22);
				*fj2 += new MenuEntry("ベストチャットON/OFF",nullptr,other23);
				*fj2 += new MenuEntry("メニューの開閉速度上昇",other3);
				*fj2 += new MenuEntry("デバッグメニュー追加",other4,"ソパカの真ん中のところに追加されます");
				*fj2 += new MenuEntry("チャット見えない",other5);
				*fj2 += new MenuEntry("チャット欄消失",other6);
				*fj2 += new MenuEntry("改行ON",other7);
				*fj2 += new MenuEntry("魚逃げない",other8);
				*fj2 += new MenuEntry("魚が一発の食いつきで釣れる",other9);
				*fj2 += new MenuEntry("タイマーカンスト",other10);
				*fj2 += new MenuEntry("動作が早くなる",other11);
				*fj2 += new MenuEntry("カメラモッド", other14, "L:遠ざける\nR:近づける");
				*fj2 += new MenuEntry("会話中に動ける",other19,"会話中に動けるようになります");
				*fj2 += new MenuEntry("マクロON",other25,"すべてのボタンを長押しすると連射になります");
				*fj2 += new MenuEntry("マクロ(Hotkey)",other26), Hotkey(Key::A,"");
			fj->Append(fj2);
			MenuFolder *fj3 = new MenuFolder("常駐OFF");
				*fj3 += new MenuEntry("掲示板メッセージ削除",nullptr, other15);
				*fj3 += new MenuEntry("デバッグメニュー表示",nullptr,other20);
				*fj3 += new MenuEntry("蜂に刺されない",other16,"蜂に刺されなくなります");
				*fj3 += new MenuEntry("蚊に刺されない",other17,"蚊に刺されなくなります");
				*fj3 += new MenuEntry("図鑑状態変更",nullptr,other27);
			fj->Append(fj3);
		
		
		MenuFolder *fk = new MenuFolder("メンテナンス");
			MenuFolder *fk1 = new MenuFolder("色変更");
				*fk1 += new MenuEntry("Set Main Text Color", nullptr, set_main_text_color);
				*fk1 += new MenuEntry("Set Menu Selected Item Color", nullptr, set_menu_selecteditem_color);
				*fk1 += new MenuEntry("Set Menu Unselected Item Color", nullptr, set_menu_unselecteditem_color);
				*fk1 += new MenuEntry("Set Window Title Color", nullptr, set_window_title_color);
				*fk1 += new MenuEntry("Set Background Border Color", nullptr, set_background_border_color);
				//*fk1 += new MenuEntry("Set Background Main Color", nullptr, set_background_main_color);
				//*fk1 += new MenuEntry("Set Background Secondary Color", nullptr, set_background_secondary_color);
			fk->Append(fk1);
				*fk += new MenuEntry("ファイル編集",nullptr,maintenance1);
				//*fk += new MenuEntry("3gx関連ファイル編集",nullptr,maintenance2);
				*fk += new MenuEntry("ファイル記入系",nullptr,maintenance3);
				*fk += new MenuEntry("Utile系",nullptr,maintenance4);
				*fk += new MenuEntry("ゲームコイン最大",maintenance5);
				*fk += new MenuEntry("ゲームコイン枚数変更",nullptr,maintenance6);
				*fk += new MenuEntry("hash表示",nullptr, HashDumper);
				*fk += new MenuEntry("軽量化",nullptr,maintenance7);
				//*fk += new MenuEntry("TestDebug",testdebug);
		
		
		*Pmenu += new MenuEntry("各種説明",nullptr,setumei2);
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
		*Pmenu += fk;
		/*メンテナンス*/
		*Pmenu += fa;
		/*クレジット*/
		

	}

	
	


	
	int main(void)
		
	{
		u64 hash = 0;
		CFGU_GenHashConsoleUnique(0, &hash);
        
		if (!(hash == 14354097094029585229)) //hash.txtの中身に書き換える
		return 0;
		
		MessageBox("チート画面で下画面の'Tools'の中の'Settings'の中の'auto'の項目4点にチェックを入れると、設定したものとFavoriteを記憶します。\n他の3gxからの変更やバージョンの変更で動作がおかしい場合は" << Color::Yellow << " CTRPFDate.bin " << Color::White << "を削除して初期設定を行ってください\n\nなにかバグ等不具合があれば" << Color::Cyan << " たいやき#5374 " << Color::White << "まで。",DialogType::DialogOk).SetClear(ClearScreen::None)();
		
		//------------------------------------------
		if ( Process::GetTitleID() != 0x0004000000086200 )
			return 0;
		
		static bool file = false;
		if(!file)
		{
		    if(!File::Exists("miku_pass.bin"))
			{
			    Keyboard    k("パスワードを入力してください");
				std::string str;
				k.Open(str);
				if(str !="Ahoy")
				{
				    (MessageBox("パスワードが違います")());
					bool select = (MessageBox("この3gxを終了します", DialogType::DialogYesNo)());;
					if(!select)
					{
					    (MessageBox("強制終了します")());
						
					}
				    abort();
				}
				else
				{
				    (MessageBox("認証完了!3gxが使用できます\n設定を反映させるために再起動してください")());
					File::Create("miku_pass.bin");
					abort();
				}
			}
			file = true;
		}
		
		u32 check_addr;
		
		while ( true )
		{
			Process::Read32(0x33099fe4, check_addr);
			if ( check_addr == 0x44 ) break;
			Sleep( Seconds(0.2) );
		}
		
		//------------------------------------------
		
		Pmenu = new PluginMenu(Color::LimeGreen << CTRPFname, 0, 1, 3, about1 + NewLINE + about2 + NewLINE + about3 + NewLINE + about4 + NewLINE + about5);
		Pmenu->SynchronizeWithFrame(true);
		OSD::Notify(Color::Cyan << "Made by Taiyaki!");
		OSD::Notify(Color::Cyan << "Loading ACNL_PLG...");
		OSD::Notify(Color::Red << "P" << 
					Color::Orange << "l" << 
					Color::Yellow << "u" <<
					Color::Lime << "g" <<
					Color::Green << "i" << 
					Color::Cyan << "n " << 
					Color::Blue << "R" <<
					Color::Purple << "e" << 
					Color::Red << "a" << 
					Color::Orange << "d" << 
					Color::Yellow << "y" << 
					Color::Lime << "!");
		Pmenu->ShowWelcomeMessage(false);
		
		Pmenu->OnNewFrame = OnNewFrameCallback;
		
		
		InitMenu();
		Pmenu->Run();
		delete Pmenu;
		return 0;
	}

}
