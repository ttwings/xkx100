// xiaolu7.c 后山小路
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "后山小路");
        set("long", @LONG
这里是后山上的小路。这条小路好象不是人工刻意修出来的，
也许只是以前的采药人踩多了，现出这样一条小路来。走到这里，
你好象迷路了。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "east" : __DIR__"xiaolu8",
                "west" : __FILE__,
                "north" : __DIR__"xiaolu3",
                "south" : __FILE__,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2690);
	set("coor/y", 120);
	set("coor/z", 170);
	setup();
        replace_program(ROOM);
}