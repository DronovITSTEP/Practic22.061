#include <iostream>
#include <io.h>
#include <stdio.h>
#include <direct.h>
#include <Windows.h>
using namespace std;

/*struct Man {
	char name[255];
	int age;
};

int main()
{
	Man man1, man2;
	cout << "Enter name -> "; cin >> man1.name;
	cout << "Enter age -> "; cin >> man1.age;
	FILE* f;
	if (!fopen_s(&f, "C:\\Text\\man.txt", "w+")) {
		fwrite(&man1, sizeof(Man), 1, f);
		fclose(f);
	}

	if (!fopen_s(&f, "C:\\Text\\man.txt", "r+")) {
		fread(&man2, sizeof(Man), 1, f);
		fclose(f);
	}
	cout << "Name: " << man2.name << ", age: " << man2.age;
}*/

/*
// stdio.h
	// rename(char* oldname, char* newname);
	// remove(const char* filename);
// io.h
	// _findfirst(char* path, _finddata_t* fileinfo);
		// unsigned attrib
			// _A_NORMAL
			// _A_RDONLY
			// _A_HIDDEN
			// _A_SYSTEM
			// _A_SUBDIR
			// _A_ARCH
		// time_t time_create
		// time_access
		// time_write
		// size
		// char name[260]
	// _findnext(size_t done, _finddate_t* fileinfo);
	// _findclose(size_t done);

void RenameFile(); // переименование файла
void RemoveFile(); // удаление файла
void Dir(); // поиск файлов в каталоге

void main(){
	cout << "Plese? select number...\n";
	char c;
	do {
		cout << "1 - Rename\n"
			<< "2 - Remove\n"
			<< "3 - View folder\n"
			<< "0 - Exit\n";
		cin >> c;

		switch (c)
		{
		case '1':
			RenameFile();
			break;
		case '2':
			RemoveFile();
			break;
		case '3':
			Dir();
			break;
		default:
			break;
		}
	} while (c != '0');
}

void RenameFile() {
	char oldname[50], newname[50];
	cout << "Enter old name -> "; cin >> oldname;
	cout << "Enter new name -> "; cin >> newname;

	if (rename(oldname, newname) != 0)
		cout << "Error!!! Couldn't rename file\n\n";
	else
		cout << "OK!\n\n";
}
void RemoveFile() {
	char name[50];
	cout << "Enter name -> "; cin >> name;

	if (remove(name) != 0)
		cout << "Error!!! Couldn't remove file\n\n";
	else
		cout << "OK!\n\n";
}
void Dir() {
	char path[70], mask[15];
	cout << "Enter full path -> "; cin >> path;
	cout << "Enter mask -> "; cin >> mask;
	strcat_s(path, mask);

	_finddata_t* fileinfo = new _finddata_t;
	size_t done = _findfirst(path, fileinfo);

	size_t mayWeWork = done;
	int count = 0;
	while (mayWeWork != -1) {
		count++;
		cout << fileinfo->name << endl;
		mayWeWork = _findnext(done, fileinfo);
	}
	cout << "Information:\twas found " << count;

	_findclose(done);
	delete fileinfo;
}
*/

/*
//direct.h
	// _mkdir(const char* dirname);
	// _rmdir(const char* dirname);

void RenameDir(); // переименование директории
void RemoveDir(); // удаление директории
void CreateDir(); // создание директории

void main() {
	cout << "Please, select number...\n";
	char c;
	do {
		cout << "1 - Rename\n"
			<< "2 - Remove\n"
			<< "3 - Create\n"
			<< "0 - Exit\n";
		cin >> c;

		switch (c)
		{
		case '1':
			RenameDir();
			break;
		case '2':
			RemoveDir();
			break;
		case '3':
			CreateDir();
			break;
		default:
			break;
		}
	} while (c != '0');
}

void RenameDir() {
	char oldname[50], newname[50];
	cout << "Enter old name -> "; cin >> oldname;
	cout << "Enter new name -> "; cin >> newname;

	if (rename(oldname, newname) != 0)
		cout << "Error!!! Couldn't rename directory\n\n";
	else
		cout << "OK!\n\n";
}
void RemoveDir() {
	char name[50];
	cout << "Enter name -> "; cin >> name;

	if (_rmdir(name) != -1)
		cout << "Error!!! Couldn't remove directory\n\n";
	else
		cout << "OK!\n\n";
}
void CreateDir() {
	char name[50];
	cout << "Enter name -> "; cin >> name;

	if (_mkdir(name) != -1)
		cout << "Error!!! Couldn't create directory\n\n";
	else
		cout << "OK!\n\n";
}*/

/*
// cd  путь
// cd ..
// cd или cd.
// exit
// root

const int size = 255;

void RemoveSpacesAndSlashes(char* str) {
	int index = strlen(str) - 1;
	while (str[index] == '\\' || str[index] == ' ')
		index--;

	strncpy_s(str, ::size, str, index+1);
	str[index + 1] = '\0';
}

void ShowCurrentDir(char path[], char temp[]) {
	printf("%s%s>", path, temp);
}

bool ShowDir(char path[]) {
	_finddata_t find;
	char pathfind[MAX_PATH];
	strcpy_s(pathfind, path);
	strcat_s(pathfind, "\\*.*");
	char info[MAX_PATH];

	size_t result = _findfirst(pathfind, &find);
	system("cls");
	size_t flag = result;
	if (flag == -1) {
		strcpy_s(info, "Такой директории нет");
		printf("%s\n", info);
		return false;
	}

	while (flag != -1) {
		if (strcmp(find.name, ".") && strcmp(find.name, "..")) {
			find.attrib& _A_SUBDIR ? strcpy_s(info, " Каталог ") :
				strcpy_s(info, " Файл ");
			printf("%30s %10s\n", find.name, info);
		}
		flag = _findnext(result, &find);
	}

	ShowCurrentDir(path, info);
	_findclose(result);
	return true;
}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char path[MAX_PATH];
	char action[::size];
	char temp[MAX_PATH];

	// получение текущего пути директории
	GetCurrentDirectoryA(sizeof(path), path);

	bool flag = true;

	ShowDir(path);
	do {
		cin.getline(action, ::size);
		RemoveSpacesAndSlashes(action);
		if (!_strcmpi(action, "root")) {
			path[2] = '\0';
			ShowDir(path);
		}
		else if (!_strcmpi(action, "exit")) flag = false;
		else if (!_strnicmp(action, "cd", 2)) {
			if (!_strcmpi(action, "cd")) {
				ShowDir(path);
			}
			else if (!_strnicmp(action, "cd", 3)) {
				int index = strspn(action + 2, " ");
				if (index) {
					if (strchr(action + index + 2, ':')) {
						if (ShowDir(action + index + 2))
							strcpy_s(path, action + index + 2);
						else
							ShowCurrentDir(path, temp);
					}
					else if (!strcmp(action + index + 2, "..")) {
						char* result = strrchr(path, '\\');
						if (result) {
							int delta = result - path;
							strncpy_s(temp, path, delta);
							temp[delta] = '\0';
						}
						else strcpy_s(temp, path);

						if (ShowDir(temp)) strcpy_s(path, temp);
						else ShowCurrentDir(path, temp);
					}
					else if (!strcmp(action + index + 2, "."))
						ShowDir(path);
					else if (!strcmp(action + index + 2, "\\"))
						ShowDir(path);
					else {
						strcpy_s(temp, path);
						strcat_s(temp, "\\");
						strcat_s(temp, action + index + 2);
						if (ShowDir(temp)) strcpy_s(path, temp);
						else ShowCurrentDir(path, temp);
					}
				}
				else ShowDir(path);
			}
			else ShowDir(path);
		}
		else ShowDir(path);
	} while (flag);
}*/

/*
int main(int args, char* argv[]) {
	char str[7] = "000000";
	char fileHTML[255] =
		"<html><head><title>New file!!!</title></head><body bgcolor = '#";
	FILE* f;
	if (!fopen_s(&f, "C:\\Text\\1.html", "w+")) {
		if (args == 2) {
			strcpy_s(str, argv[1]);
		}
		strcat_s(fileHTML, str);
		strcat_s(fileHTML, "'></body></html>");
		fputs(fileHTML, f);
		fclose(f);
		cout << "Ok...";
	}
}
*/