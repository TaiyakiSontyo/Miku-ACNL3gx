#include "cheats.hpp"

#include <string>
#include <cstdio>
#include <vector>


namespace CTRPluginFramework
{

	u8 red_value = 255;
	u8 green_value = 255;
	u8 blue_value = 255;


	// Thanks: https://pyopyopyo.hatenablog.com/entry/2019/02/08/102456
	template <typename ... Args>
	std::string format(const std::string& fmt, Args ... args ) {
			size_t len = std::snprintf( nullptr, 0, fmt.c_str(), args ... );
			std::vector<char> buf(len + 1);
			std::snprintf(&buf[0], len + 1, fmt.c_str(), args ... );
			return std::string(&buf[0], &buf[0] + len);
	}


	std::string make_color_message(u8 r, u8 g, u8 b) {
		return format("10進数: " << Color::Red << "R[%03d] " << Color::Green << "G[%03d] " << Color::Blue << "B[%03d]\n", r, g, b) <<
			Color::White <<
			format("16進数: " << Color::Red << "R[%02X] " << Color::Green << "G[%02X] " << Color::Blue << "B[%02X]\n\n\n", r, g, b) <<
			Color(red_value, green_value, blue_value) <<
			"■■■■■■■■■■■■■■■■■■■■■■■■■\n" <<
			"これは参考用の色のテスト表示です\n" <<
			"This is a test display of\n" <<
			" colors for reference\n" <<
			"■■■■■■■■■■■■■■■■■■■■■■■■■";
	}


	u8 color_input(const std::string& color_name) {
		u8 value = 0;
		Keyboard keyboard("進数を選択してください", {"10進数", "16進数"});
		keyboard.CanAbort(false);
		int choice = keyboard.Open();

		Keyboard input_u8(color_name << "の値を入力してください");
		input_u8.CanAbort(false);

		if (choice == 0) {
			input_u8.IsHexadecimal(false);
			input_u8.SetMaxLength(3);
			input_u8.OnInputChange(
				[](Keyboard &kbd, InputChangeEvent &evt) {
					if (evt.type == InputChangeEvent::CharacterAdded) {
						std::string &input = kbd.GetInput();
						std::string &message = kbd.GetMessage();
						int value = std::stoi(input);
						if (255 < value) {
							input = "255";
						}
					}
				}
			);
			input_u8.Open(value);
		}
		else if (choice == 1) {
			input_u8.IsHexadecimal(true);
			input_u8.SetMaxLength(2);
			input_u8.OnInputChange(
				[](Keyboard &keyboard, InputChangeEvent &event) {
					if (event.type == InputChangeEvent::CharacterAdded) {
						std::string &input = keyboard.GetInput();
						unsigned int value = std::stoul(input, nullptr, 16);
						if (255 < value) {
							input = "255";
						}
					}
				}
			);
			input_u8.Open(value);
		}
		return value;
	}


	void set_background_border_color(MenuEntry *entry) {
		if (File::Exists("color.bin")) {
			File file;
			File::Open(file,"color.bin");
			file.Read((void*)&red_value, sizeof(u8));
			file.Seek(1);
			file.Read((void*)&green_value, sizeof(u8));
			file.Seek(1);
			file.Read((void*)&blue_value, sizeof(u8));
			file.Close();
		}

		Keyboard keyboard(
			make_color_message(red_value, green_value, blue_value),
			{
				"赤の値を入力",
				"緑の値を入力",
				"青の値を入力",
				"結果表示"
			}
		);

		int choice = keyboard.Open();

		if (choice == 0) {
			red_value = color_input(Color::Red << "赤" << Color::White);
		}
		else if (choice == 1) {
			green_value = color_input(Color::Green << "緑" << Color::White);
		}
		else if (choice == 2) {
			blue_value = color_input(Color::Blue << "青" << Color::White);
		}
		else if (choice == 3) {
			MessageBox(
				Color(red_value, green_value, blue_value) <<
				("■■■■■■■■■\n■■■■■■■■■\n■■■■■■■■■")
			)();
		}

		FwkSettings &settings = FwkSettings::Get();
		settings.BackgroundBorderColor = Color(red_value, green_value, blue_value);

		if (!File::Exists("color.bin")) {
			File::Create("color.bin");
		}

		File file;
		File::Open(file, "color.bin");
		file.Write((void*)&red_value, sizeof(u8));
		file.Seek(1);
		file.Write((void*)&green_value, sizeof(u8));
		file.Seek(1);
		file.Write((void*)&blue_value, sizeof(u8));
		file.Flush();
		file.Close();
	}

}