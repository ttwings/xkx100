inherit ROOM;

void create()
{
	set("short", "�ŵ�����");
	set("long", @LONG
������С�����࣬һ�ɺ��紵���������ɪɪ������ֻ���뿪��
LONG );

	set("resource/water", 1);
	set("exits", ([
		"east" : __DIR__"bridge",
	]));
	set("no_clean_up", 0);
	set("coor/x", -210);
	set("coor/y", 5000);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}