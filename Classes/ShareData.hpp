#ifndef __SHARE_DATA__
#define __SHARE_DATA__
class ShareData{
public :
	static char username[20];
	static int userid;
	static int face;
	static int rank;
	static int magicBubbleNum;
	ShareData(){
		username[0]='a';
		userid=1;
		face=1;
		rank=1;
		magicBubbleNum=1;
	}
};
char ShareData::username[20];
int ShareData::userid;
int ShareData::face;
int ShareData::rank;
int ShareData::magicBubbleNum;
#endif
