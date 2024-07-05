

#ifndef IMG_PROC_CMDLINEPARSER_H
#define IMG_PROC_CMDLINEPARSER_H

#include "iostream"
#include <string_view>
#include <vector>
// Описатель фильтра, который будет извлечён из командной строчки, сожержит:
// название фильтра без ведущего дефиса, параметры фильтра (коллекция) На этом
// этапе будем считать наиболее универсальным представлением параметров строку.

// Хранит описатель одного фильтра, извлечённого из параметров командной строки.
// Т.к. использует string_view, который не является владеющим классом, мы должны
// гарантировать, что подлежащий под ним указатель указывает на объект, время
// жизни которого гарантированно дольше фильтр-дескриптора. Для параметров
// командной строки это можно гарантировать. Если бы использовали char*, мы
// всего лишь обещали бы '\0' в конце, а все остальные требования остались бы
// прежними. Если бы необходимо было сделать дескриптор владеющим объектом, то
// можно было бы использовать string.
class FilterDescriptor {
public:
  explicit FilterDescriptor(std::string &filter) : filter_(filter) {}

  std::string GetFilterName() const { return filter_; }

  const std::vector<std::string> &GetFilterParams() const { return params_; }

  void AddParam(std::string param) { params_.push_back(param); }

private:
  std::string filter_;
  std::vector<std::string> params_;
};

// Следующий класс, который мы напишем, -- это CmdLineParser.
// Параметры argc, ardv можем передвать через конструктор, или через функцию
// Parse, или ещё как-то.
class CmdLineParser {
private:
  std::vector<FilterDescriptor> filters_;
  // Использовать string_view для названия файлом крайне неудачно, поэтому будем
  // использовать char* или std::string Т.к. мы не сможем открыть такой файл
  // c-шными функциям, требующиеми c-style строки.
  // std::string input_;
  char *input_file_;
  char *output_file_;

  // функция для визуальной проверки полученных значений
  void RevealFiltersList();

  void ExtractFilters(int argc, char *argv[]);

public:
  CmdLineParser(int argc, char *argv[]);

  std::vector<FilterDescriptor> &GetFilters() { return filters_; }

  char *GetOutputFile() const { return output_file_; }

  char *GetInputFile() const { return input_file_; }
};

#endif // IMG_PROC_CMDLINEPARSER_H
