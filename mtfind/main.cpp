
#include <iostream>

#include "FindData.h"

#if defined(USE_PERFCOUNTER)
#include <windows.h>
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
  LARGE_INTEGER li;
  QueryPerformanceFrequency(&li);
  PCFreq = double(li.QuadPart) / 1000.0;
  QueryPerformanceCounter(&li);
  CounterStart = li.QuadPart;
}

double GetCounter()
{
  LARGE_INTEGER li;
  QueryPerformanceCounter(&li);
  return double(li.QuadPart - CounterStart) / PCFreq;
}
#endif

void ShowUsage()
{
  std::cout << "Find all strings in the file by the mask." << std::endl;
  std::cout << "Usage:" << std::endl << " mtfind filename mask" << std::endl;
}

int main(int argc, char** argv)
{
  if (argc <= 2)
  {
    ShowUsage();
    system("pause");
    return 1;
  }

  const char* filename = argv[1];
  const char* mask = argv[2];

#if defined(USE_PERFCOUNTER)
  //std::cout << filename << " " << mask << std::endl;
  StartCounter();
#endif

  FindData findData(filename, mask);
  findData.BeginFinding(WAIT_ENDING);

#if defined(USE_PERFCOUNTER)
  auto findingCounter = GetCounter();
  StartCounter();
#endif

  std::cout << "Result:" << std::endl;
  auto found = findData.GetFound();
  std::cout << found.size() << std::endl;
  for (auto i = 0; i < found.size(); ++i)
  {
    FoundData& fdata = found.at(i);

    std::cout << fdata.lineNum << " "
      << fdata.columnNum << " "
      << fdata.data << std::endl;
  }


#if defined(USE_PERFCOUNTER)
  std::cout << "\nFinding : " << findingCounter << " ms" << std::endl;
  std::cout << "Printing: " << GetCounter() << " ms" << std::endl;
#endif
  system("pause");

  return 0;
}