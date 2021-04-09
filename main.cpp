#include <iostream>
#include <string>
#include <filesystem>
#include <clocale>
#include <algorithm>
#include <cwctype>

using namespace std;
namespace fs = std::filesystem;


void translit(const wstring& in, wstring& out);
void showHelp();

int wmain(int argc, wchar_t** argv) {
	//setlocale(LC_CTYPE, "rus");
	setlocale(LC_ALL, "Russian");
	
	if (argc < 2)
	{
		showHelp();
		return 0;
	}
	
	bool isDryRun = false;
	
	for (int i = 1; i < argc; i++)
	{
		wstring arg = argv[i];
		
		if (arg == L"--help")
		{
			showHelp();
			break;
		}
		if (arg == L"--dry-run")
		{
			isDryRun = true;
		}
		else
		{
			fs::path oldPath(arg);
			wstring oldFilename = oldPath.filename().wstring();
			wstring newFilename;
			translit(oldFilename, newFilename);
			wcout << oldFilename << L" --> " << newFilename << endl;
			fs::path newPath(oldPath);
			newPath.replace_filename(newFilename);
			
			if (!isDryRun)
			{
				try
				{
					fs::rename(oldPath, newPath);
				}
				catch (const exception& error)
				{
					/*wcout*/ wcerr << L"!!! Ошибка обработки файла \"" << oldPath.wstring() << "\":" << endl;
					/*wcout*/ wcerr << "" << error.what() << endl;
				}
			}
		}
	}
	
	
	//system("PAUSE");
	return 0;
}

void showHelp()
{
	//string exeName = getFileName(argv[0], true, "\\");
	const wstring exeName = L"translit.exe";
	
	wcout << L"Использование: " << exeName << L" [--help] [--dry-run] [FILENAME]..." << endl;
	wcout << endl;
	wcout << L"Параметры:" << endl;
	wcout << L"\t--help\t\t- Показать справку" << endl;
	wcout << L"\t--dry-run\t- Имитация переименования" << endl;
	wcout << L"\tFILENAME\t- Имена одного или более файлов" << endl;
}

void translit(const wstring& in, wstring& out)
{
	out = L"";
	
	for (int i = 0; i < in.length(); i++)
	{
		/*unsigned*/ wchar_t oldChar = in[i];
		/*unsigned*/ wchar_t lowerOldChar = towlower(oldChar);
		//cout << "char=" << oldChar << " lower=" << lowerOldChar << endl;
		wstring newChar = L"";
		
		switch (lowerOldChar)
		{
			case L'а':
				newChar = L"a";
				break;
				
			case L'б':
				newChar = L"b";
				break;
					
			case L'в':
				newChar = L"v";
				break;
					
			case L'г':
				newChar = L"g";
				break;
				
			case L'д':
				newChar = L"d";
				break;
				
			case L'е':
				newChar = L"e";
				break;
				
			case L'ё':
				newChar = L"yo"; // e
				break;
				
			case L'ж':
				newChar = L"zh"; // j
				break;
				
			case L'з':
				newChar = L"z";
				break;
				
			case L'и':
				newChar = L"i";
				break;
				
			case L'й':
				newChar = L"y"; // y/j
				break;
				
			case L'к':
				newChar = L"k";
				break;
			
			case L'л':
				newChar = L"l";
				break;
				
			case L'м':
				newChar = L"m";
				break;
			
			case L'н':
				newChar = L"n";
				break;
				
			case L'о':
				newChar = L"o";
				break;
						
			case L'п':
				newChar = L"p";
				break;
							
			case L'р':
				newChar = L"r";
				break;
					
			case L'с':
				newChar = L"s";
				break;
						
			case L'т':
				newChar = L"t";
				break;
				
			case L'у':
				newChar = L"u";
				break;
				
			case L'ф':
				newChar = L"f";
				break;
				
			case L'х':
				newChar = L"h";
				break;
				
			case L'ц':
				newChar = L"ts"; // ts/c
				break;
				
			case L'ч':
				newChar = L"ch";
				break;
				
			case L'ш':
				newChar = L"sh";
				break;
				
			case L'щ':
				newChar = L"sch";
				break;
				
			case L'ъ':
				newChar = L""; // пропускаем
				break;
				
			case L'ы':
				newChar = L"y"; // y/i
				break;
				
			case L'ь':
				newChar = L""; // пропускаем
				break;
				
			case L'э':
				newChar = L"e"; // e/eh
				break;
				
			case L'ю':
				newChar = L"yu";
				break;
				
			case L'я':
				newChar = L"ya";
				break;
				
			default:
				// Остальные символы оставляем как есть
				newChar = oldChar;
				break;
		}
		
		if (iswupper(oldChar))
		{
			//transform(newChar.begin(), newChar.end(),newChar.begin(), towupper); // to upper
			if (newChar.length() >= 1)
				newChar[0] = towupper(newChar[0]); // Capitalize
		}
					
		out += newChar;
	}
}