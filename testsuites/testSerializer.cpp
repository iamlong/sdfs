#include "../util/serializer.h"

#include <gtest/gtest.h>
#include <string.h>

class testser : public ISerialize {
		public:
		testser(){
				m_start_sig[0] ='T';
				m_start_sig[1] ='T';
				m_end_sig[0]='T';
				m_end_sig[0]='T';
				getPersistentSizeInByte();
				a = 10;
				b = 20;
				strcpy(c, "abcdef");
				
		};
		
		int getPersistentSizeInByte(){
				m_persistent_size = sizeof(a)+sizeof(b)+sizeof(c)+getISerializeSize();
				return m_persistent_size;
		};
		
		bool Serialize(Serializer * inSerializer){
			inSerializer->fillBytes((uint8_t *)m_start_sig, sizeof(m_start_sig));
			inSerializer->fillBytes((uint8_t *)&m_persistent_size, sizeof(m_persistent_size));
			inSerializer->fillBytes((uint8_t *)&a, sizeof(a));
			inSerializer->fillBytes((uint8_t *)&a, sizeof(b));
			inSerializer->fillBytes((uint8_t *)c, sizeof(c));
			inSerializer->fillBytes((uint8_t *)m_end_sig, sizeof(m_end_sig));
			
		}
		
		bool DeSerialize(uint8_t * buff, int buff_size){
			return true;
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


int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
