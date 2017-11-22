#include "EUtil.h"

namespace E3D
{
	std::ofstream* GLogStream = nullptr;

	bool InitLog(const EString& filename)
	{
		if (GLogStream == nullptr)
		{
			GLogStream = new std::ofstream();
			GLogStream->open(filename.c_str());
			if (GLogStream->good())
				return true;

			return false;
		}
		return true;
	}

	void Log(const EChar* string, ...)
	{
		if (GLogStream == nullptr)
			return;

		EChar buffer[256];

		//保证两者都不为空
		if (!string || !GLogStream)
			return;

		va_list arglist; //可变参数列表
		//利用在栈上的可变的参数打印输出字符串
		va_start(arglist, string);
		vsprintf_s(buffer, string, arglist);
		va_end(arglist);

		EString info(buffer);
		//输出信息流
		*GLogStream << info << std::endl;
		GLogStream->flush();
	}

	void CloseLog()
	{
		GLogStream->close();
		SafeDelete(GLogStream);
	}

}