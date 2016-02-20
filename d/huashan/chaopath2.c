// Room: chaopath2.c ������С·
//Date: Oct. 2 1997 by Venus

inherit ROOM;

void create()
{
	set("short","������С·");
	set("long",@LONG
�����ǳ�����С·��ɽ�ƶ��ͣ�����������ȣ�һ��С�Ķ������
��ȥ��������һ��С·������û����
LONG);
	set("outdoors", "huashan");
	set("exits",([ /* sizeof() == 1 */
		"eastup"   : __DIR__"chaoyang",
		"westup"   : __DIR__"ziqitai",
		"southwest": __DIR__"chaopath1",
	]));
	set("objects", ([
		__DIR__"npc/shi-daizi" : 1,
	]));
	set("coor/x", -860);
	set("coor/y", 220);
	set("coor/z", 120);
	setup();
}
 
void init()
{
	object me = this_player();
	if (me->query_temp("xunshan")) me->set_temp("xunshan/chaoyang", 1);
	return;
}

int valid_leave(object me, string dir)
{
	if (dir=="eastup" &&
		objectp(present("shi daizi", environment(me))) &&
		(me->query("family/master_id")!="gao laozhe") &&
		(me->query("family/master_id")!="ai laozhe"))
		return notify_fail("ʩ���Ӻȵ�����������λ��������֮������λ" + RANK_D->query_respect(me) + "��ֹ����\n");
	return ::valid_leave(me, dir);
}