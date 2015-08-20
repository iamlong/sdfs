#include "../util/serializer.h"

#include <gtest/gtest.h>
#include <string.h>

class testser : public ISerialize {
		public:
		testser(){
				char startsig[]="TT";
				char endsig[]="TT";
				memcpy(m_start_sig, startsig, sizeof(m_start_sig));
				memcpy(m_end_sig, startsig, sizeof(m_end_sig));
				getPersistentSizeInByte();
				a = 10;
				b = 20;
				strcpy(c, "abcdef");
				
		};
		
		void reseta(int newa){a=newa;};
		
		
		int getPersistentSizeInByte(){
				m_persistent_size = sizeof(a)+sizeof(b)+sizeof(c)+getISerializeSize();
				return m_persistent_size;
		};
		
		bool Serialize(Serializer * inSerializer){
			inSerializer->fillBytes((uint8_t *)m_start_sig, sizeof(m_start_sig));
			inSerializer->fillBytes((uint8_t *)&m_persistent_size, sizeof(m_persistent_size));
			inSerializer->fillBytes((uint8_t *)&a, sizeof(a));
			inSerializer->fillBytes((uint8_t *)&b, sizeof(b));
			inSerializer->fillBytes((uint8_t *)c, sizeof(c));
			inSerializer->fillBytes((uint8_t *)m_end_sig, sizeof(m_end_sig));
			
		}
		
		bool DeSerialize(DeSerializer * inDeSerializer){
			uint8_t sig[2];
			
			inDeSerializer->pullBytes(sig, 2);
			if(sig[0]!='T'&&sig[1]!='T')
					return false;
			
			inDeSerializer->pullBytes((uint8_t *)&m_persistent_size, sizeof(m_persistent_size));
			inDeSerializer->pullBytes((uint8_t *)&a, sizeof(a));
			inDeSerializer->pullBytes((uint8_t *)&b, sizeof(b));
			inDeSerializer->pullBytes((uint8_t *)c, sizeof(c));
			
			inDeSerializer->pullBytes(sig, 2);
			if(sig[0]!='T'&&sig[1]!='T')
					return false;
			return true;
		}
		
		bool operator==(const testser& comp ){
			bool ret = (a==comp.a&&b==comp.b);
			for(int i = 0; i<10; i++)
				ret = (c[i]==comp.c[i])&&ret;
			return ret;
		}
		
		private:
			int a;
			int b;
			char c[10];
};

TEST (SERIALIZERTEST, FILLBYTES) {
	
	Serializer a(10); //create a buffer with 
	
	ASSERT_EQ(10, a.getSize());
	
	ASSERT_TRUE(a.fillBytes((uint8_t *)"abcd", sizeof("abcd")));
	
	ASSERT_EQ(5, a.getUsedSize());
	
	ASSERT_STREQ("abcd", (char *)a.getFilledBuffer());
	
	ASSERT_TRUE(a.fillBytes((uint8_t *)"abcd", sizeof("abcd")));
	
	ASSERT_STREQ("abcd", (char *)a.getFilledBuffer());
	ASSERT_STREQ("abcd", (char *)(a.getFilledBuffer()+5));
	
	ASSERT_FALSE(a.fillBytes((uint8_t *)"abcd", sizeof("abcd")));

}

TEST (SERIALIZERTEST, FILLOBJECT) {
	
	testser t1;
	
	Serializer a(t1.getPersistentSizeInByte()); //create a buffer with 
	
	ASSERT_EQ(18+8, a.getSize());

	ASSERT_TRUE(a.fillObject(&t1));
	
	ASSERT_EQ(18+8, a.getUsedSize());
	

	
}

TEST (SERIALIZERTEST, PULLOBJECT) {
	
	testser t1;
	
	Serializer a(t1.getPersistentSizeInByte()); //create a buffer with 
	
	ASSERT_EQ(18+8, a.getSize());

	ASSERT_TRUE(a.fillObject(&t1));
	
	ASSERT_EQ(18+8, a.getUsedSize());
	
	testser t2;
	
	DeSerializer b (a.getFilledBuffer(), a.getSize());
	b.pullObject(&t2);
	
	ASSERT_TRUE(t2==t1);
	
	t1.reseta(330);
	ASSERT_FALSE(t2==t1);
	
	

	
}

int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
