#include <iostream>
#include <string>
#include <cctype>
#include <filesystem>
#include <clocale>
#include <algorithm>
//#include <wchar.h>
#include <stringapiset.h>

using namespace std;
namespace fs = std::filesystem;


void translit(const string& in, string& out);
string getFileName(const string& filePath, bool withExtension = true, char seperator = '/');
std::string cp1251_to_utf8(const char *str);

int main(int argc, char** argv) {
	//setlocale(LC_CTYPE, "rus");
	setlocale(LC_ALL, "Russian");
	
	for (int i = 1; i < argc; i++)
	{
		string fullpath = argv[i];
		//cout << "fullpath=" << fullpath << endl;
		string filename = /*fs::path(fullpath).filename().string()*/ getFileName(fullpath, true, '\\');
		//cout << "old filename=" << filename << endl;
		string newFilename = "";
		translit(filename, newFilename);
		cout << filename << " --> " << newFilename << endl;
		
		/*fullpath = cp1251_to_utf8(fullpath.c_str());
		newFilename = cp1251_to_utf8(newFilename.c_str());*/
		fs::rename(fullpath, newFilename);
	}
	
	
	//system("PAUSE");
	return 0;
}

/*
 * Get File Name from a Path with or without extension
 */
string getFileName(const string& filePath, bool withExtension, char separator)
{
    // Get last dot position
    std::size_t dotPos = filePath.rfind('.');
    std::size_t sepPos = filePath.rfind(separator);
    if(sepPos != std::string::npos)
    {
        return filePath.substr(sepPos + 1, filePath.size() - (withExtension || dotPos != std::string::npos ? 1 : dotPos) );
    }
    return "";
}

void translit(const string& in, string& out)
{
	out = "";
	
	for (int i = 0; i < in.length(); i++)
	{
		unsigned char oldChar = in[i];
		unsigned char lowerOldChar = tolower(in[i]);
		//cout << "char=" << oldChar << " lower=" << lowerOldChar << endl;
		string newChar;
		
		//cout << "lower=" << (char)(tolower(in[i])) << endl;
		
		switch (lowerOldChar)
		{
			case /*'а'*/ 224:
				newChar = "a";
				break;
				
			case /*'б'*/ 225:
				newChar = "b";
				break;
					
			case /*'в'*/ 226:
				newChar = "v";
				break;
					
			case /*'г'*/ 227:
				newChar = "g";
				break;
				
			case /*'д'*/ 228:
				newChar = "d";
				break;
				
				
			case /*'е'*/ 229:
				newChar = "e";
				break;
				
				
			case /*'ё'*/ 184:
				newChar = "yo"; // e
				break;
				
				
			case /*'ж'*/ 230:
				newChar = "zh"; // j
				break;
				
				
			case /*'з'*/ 231:
				newChar = "z";
				break;
				
				
			case /*'и'*/ 232:
				newChar = "i";
				break;
				
			case /*'й'*/ 233:
				newChar = "y"; // y/j
				break;
				
			case /*'к'*/ 234:
				newChar = "k";
				break;
			
			case /*'л'*/ 235:
				newChar = "l";
				break;
				
			case /*'м'*/ 236:
				newChar = "m";
				break;
			
			case /*'н'*/ 237:
				newChar = "n";
				break;
				
			case /*'о'*/ 238:
				newChar = "o";
				break;
						
			case /*'п'*/ 239:
				newChar = "p";
				break;
							
			case /*'р'*/ 240:
				newChar = "r";
				break;
					
			case /*'с'*/ 241:
				newChar = "s";
				break;
						
			case /*'т'*/ 242:
				newChar = "t";
				break;
				
			case /*'у'*/ 243:
				newChar = "u";
				break;
				
			case /*'ф'*/ 244:
				newChar = "f";
				break;
				
			case /*'х'*/ 245:
				newChar = "h";
				break;
				
			case /*'ц'*/ 246:
				newChar = "ts"; // ts/c
				break;
				
			case /*'ч'*/ 247:
				newChar = "ch";
				break;
				
			case /*'ш'*/ 248:
				newChar = "sh";
				break;
				
			case /*'щ'*/ 249:
				newChar = "sch";
				break;
				
			case /*'Ъ'*/ 250:
				newChar = ""; // пропускаем
				break;
				
			case /*'ы'*/ 251:
				newChar = "y"; // y/i
				break;
				
			case /*'ь'*/ 252:
				newChar = ""; // пропускаем
				break;
				
			case /*'э'*/ 253:
				newChar = "e"; // e/eh
				break;
				
			case /*'ю'*/ 254:
				newChar = "yu";
				break;
				
			case /*'я'*/ 255:
				newChar = "ya";
				break;
				
			default:
				// Остальные символы оставляем как есть
				newChar = in[i];
				break;
				
		}
		
		if (isupper(oldChar))
			transform(newChar.begin(), newChar.end(),newChar.begin(), ::toupper); // to upper
					
		out += newChar;
		
	}
}

std::string cp1251_to_utf8(const char *str)
{
    std::string res;
    /*WCHAR*/ wchar_t *ures = NULL;
    char *cres = NULL;
 
    int result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
    if (result_u != 0)
    {
        ures = new WCHAR[result_u];
        if (MultiByteToWideChar(1251, 0, str, -1, ures, result_u))
        {
            int result_c = WideCharToMultiByte(CP_UTF8, 0, ures, -1, 0, 0, 0, 0);
            if (result_c != 0)
            {
                cres = new char[result_c];
                if (WideCharToMultiByte(CP_UTF8, 0, ures, -1, cres, result_c, 0, 0))
                {
                    res = cres;
                }
            }
        }
    }
 
    delete[] ures;
    delete[] cres;
 
    return res;
}