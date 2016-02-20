// Room: /d/chengdu/npc/smith.c
// Last Modifyed by Winder on Jan. 4 2002

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("����", ({ "tiejiang", "smith" }));
	set("title", "�������ϰ�");
	set("shen_type", 1);

	set("gender", "����" );
	set("age", 33);
	set("long", "����������ǯ��סһ����ȵ�����Ž�¯�С�\n");

	set("combat_exp", 400);
	set("attitude", "friendly");
	set("vendor_goods",({
		WEAPON_DIR"changjian",
		WEAPON_DIR"hammer",
		WEAPON_DIR"dagger",
		WEAPON_DIR"gangdao",
		WEAPON_DIR"muchui",
		WEAPON_DIR"qimeigun",
	}));

	setup();

	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}

/*
int buy_object(object who, string what)
{
	if( what=="hammer" ) return 300;
	if( what=="changjian" ) return 700;
	return 0;
}

void compelete_trade(object who, string what)
{
	object ob;
	
	if( what=="hammer" )  ob = new(__DIR__"obj/hammer");
	if( what=="changjian" )  ob = new(__DIR__"changjian");
	ob->move(who);
	if( what=="hammer" )
message_vision("$N����$nһ������Ĵ�����������\n", this_object(), who);
	if( what=="changjian" )
message_vision("$N����$nһ����������ĳ�����\n", this_object(), who);
}
*/ 