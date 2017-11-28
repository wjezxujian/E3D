#pragma once

namespace E3D
{
	//Ogre Mesh 文件相关信息

	//Ogre Mesh 二进制文件中的ID枚举 来源Ogre
	enum class OGREMESHID
	{
		//无符号短整数
		M_HEADER = 0x1000,
		//版本信息
		M_MESH = 0x3000,
		//子网格信息
		M_SUBMESH = 0x4000,

		//M_GEOMETRY块（变量useSharedVetrices = false时才会出现）
		M_GEOMERTY = 0x5000, //这个块是被嵌入在网格和子网格中
		//顶点数量
		M_GEOMETRY_VERTEX_DECLARATION = 0x5100,
		M_GEOMETRY_VERTEX_ELEMENT = 0x5110, //重复数据
		M_GEOMETRY_VERTEX_BUFFER = 0x5200, //重复的数据
		M_GEOMETRY_VERTEX_BUFFER_DATA = 0x5210,
		
		M_SUBMESH_OPERATION = 0x4010, //可选项
		M_MESH_BOUNDS = 0x9000,
		M_SUBMESH_NAME_TABLE = 0xA000,
		//子块名字列表，每个子块包括索引和字符串
		M_SUBMESH_NAME_TABLE_ELEMENT = 0xA100,
	};

	//渲染类型枚举
	enum class OperationType
	{
		//点的列表
		OT_POINT_LIST = 1,
		//线列表，一条线包括两个顶点
		OT_LINE_LIST = 2,
		//带状连接线
		OT_LINE_STRIP = 3,
		//三角形列表
		OT_TRIANGLE_LIST = 4,
		//带状三角形
		OT_TRIANGLE_STRIP = 5,
		//三角形扇
		OT_TRIANGLE_FAN = 6,
	};
}