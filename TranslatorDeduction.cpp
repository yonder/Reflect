#include "ReflectPch.h"
#include "Reflect/TranslatorDeduction.h"
#include "Reflect/Object.h"

using namespace Helium;
using namespace Reflect;

#if !HELIUM_RELEASE

struct TestEnumeration : Reflect::EnumerationBase
{
public:
	enum Enum
	{
		ValueOne,
		ValueTwo,
	};

	REFLECT_DECLARE_ENUMERATION( TestEnumeration );
	static void EnumerateEnum( Helium::Reflect::Enumeration& info );
};

REFLECT_DEFINE_ENUMERATION( TestEnumeration );

void TestEnumeration::EnumerateEnum( Helium::Reflect::Enumeration& info )
{
	info.AddElement( ValueOne, TXT( "Value One" ) );
	info.AddElement( ValueTwo, TXT( "Value Two" ) );
}

struct TestStruct : StructureBase
{
	REFLECT_DECLARE_BASE_STRUCTURE( TestStruct );
	static void PopulateStructure( Reflect::Structure& comp );

	uint8_t  m_Uint8;
	uint16_t m_Uint16;
	uint32_t m_Uint32;
	uint64_t m_Uint64;

	int8_t  m_Int8;
	int16_t m_Int16;
	int32_t m_Int32;
	int64_t m_Int64;

	float32_t m_Float32;
	float64_t m_Float64;

    std::vector<uint32_t> m_StdVectorUint32;
    std::set<uint32_t> m_StdSetUint32;
    std::map<uint32_t, uint32_t> m_StdMapUint32;
    
    DynamicArray<uint32_t> m_FoundationDynamicArrayUint32;
    Set<uint32_t> m_FoundationSetUint32;
    Map<uint32_t, uint32_t> m_FoundationMapUint32;
};

REFLECT_DEFINE_BASE_STRUCTURE( TestStruct );

void TestStruct::PopulateStructure( Reflect::Structure& comp )
{
	comp.AddField( &TestStruct::m_Uint8,  "Unsigned 8-bit Integer" );
	comp.AddField( &TestStruct::m_Uint16, "Unsigned 16-bit Integer" );
	comp.AddField( &TestStruct::m_Uint32, "Unsigned 32-bit Integer" );
	comp.AddField( &TestStruct::m_Uint64, "Unsigned 64-bit Integer" );

	comp.AddField( &TestStruct::m_Int8,  "Signed 8-bit Integer" );
	comp.AddField( &TestStruct::m_Int16, "Signed 16-bit Integer" );
	comp.AddField( &TestStruct::m_Int32, "Signed 32-bit Integer" );
	comp.AddField( &TestStruct::m_Int64, "Signed 64-bit Integer" );

	comp.AddField( &TestStruct::m_Float32, "32-bit Floating Point" );
	comp.AddField( &TestStruct::m_Float64, "64-bit Floating Point" );
    
	comp.AddField( &TestStruct::m_StdVectorUint32, "std::vector of Signed 32-bit Integers" );
	comp.AddField( &TestStruct::m_StdSetUint32, "std::vector of Unsigned 32-bit Integers" );
	comp.AddField( &TestStruct::m_StdMapUint32, "std::map of Unsigned 32-bit Integers" );
    
	comp.AddField( &TestStruct::m_FoundationDynamicArrayUint32, "Dynamic Array of Signed 32-bit Integers" );
	comp.AddField( &TestStruct::m_FoundationSetUint32, "Set of Unsigned 32-bit Integers" );
	comp.AddField( &TestStruct::m_FoundationMapUint32, "Map of Unsigned 32-bit Integers" );
}

class TestObject : public Reflect::Object
{
public:
	REFLECT_DECLARE_OBJECT( TestObject, Reflect::Object );
	static void PopulateStructure( Reflect::Structure& comp );

private:
	TestStruct m_Struct;
	TestStruct m_StructArray[ 8 ];

	TestEnumeration m_Enumeration;
	TestEnumeration m_EnumerationArray[ 8 ];
};

REFLECT_DEFINE_OBJECT( TestObject );

void TestObject::PopulateStructure( Reflect::Structure& comp )
{
	comp.AddField( &TestObject::m_Struct, "Structure" );
	comp.AddField( &TestObject::m_StructArray, "Structure Array" );

	comp.AddField( &TestObject::m_Enumeration, "Enumeration" );
	comp.AddField( &TestObject::m_EnumerationArray, "Enumeration Array" );
}

void Func()
{
	AllocateTranslator< uint8_t >();
	AllocateTranslator< TestStruct >();
	AllocateTranslator< ObjectPtr >();

	StrongPtr< TestObject > object = new TestObject ();
}

#endif