#include "cheats.hpp"
#include "ctrulib\services\cfgu.h"

namespace CTRPluginFramework
{
	void HashDumper(MenuEntry *entry)
    {
		Keyboard key("hashをダンプします",{"実行"});
		int r = key.Open();
		if ( r == 0 ) {
			u64 hash = 0;
			File::Create("hash.txt");
			CFGU_GenHashConsoleUnique(0, &hash);
			File file;
			File::Open(file, "hash.txt", File::RWC);
			file.WriteLine(std::to_string(hash));
			file.Close();
			(MessageBox("ハッシュをダンプしました\nhash.txtを確認してください"))();
		}
    }
}

