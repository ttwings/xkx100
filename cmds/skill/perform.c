// perform.c
// modified by sega 99/1/16
// ���ӱ���perform���ƣ��ο�/d/city/npc/referee.c modified by sega 2000/02/05
// ��ת����
// hubo��˫��pfm by qingyun 04/9/25
//inherit F_CLEAN_UP;lijia
inherit F_SSERVER;

#include <ansi.h>


string *prep_skl = ({"finger","hand","cuff","claw","strike","unarmed","leg"});
private int do_perform(object me, string arg);

int main(object me, string arg)
{
	string and;//�ڶ���pfm
	int result;
  int busy;
  int lvl;
  int suc;
  string msg="\n";
	object target;
	seteuid(getuid());

	if( me->is_busy() )
			return notify_fail("( ����һ��������û����ɣ�����ʩ���⹦��)\n");
//	if ( environment(me)->is_chat_room())
//      return notify_fail("�����ֹ�򶷡�\n");
	if( !living(me) || me->query_temp("noliving") )
			return notify_fail("���н��ε����޷�ʩ���⹦��\n");
	if (me->query("jing") < 0 || me->query("qi") < 0)
			return notify_fail("���н��ε����޷�ʩ���⹦��\n");
	if( me->query_temp("bixie/ciwan") )
			return notify_fail("����������ˣ�����ʩ���⹦��\n");
	if( me->query_temp("dagou/feng") )
			return notify_fail("�����ʽ���򹷰���ס������ʩ���⹦��\n");
	if( !arg ) 
			return notify_fail("��Ҫ���⹦��ʲô��\n");
  if (me->query_temp("no_perform"))
    	return notify_fail(HIR "��ֻ��ȫ���������ƻ�ɢ��һ�㣬ȫȻ�޷����ơ�\n" NOR);

//����perform����
	
	if (me->query_temp("biwu/perform_time"))
	{
		if (time()-(int)me->query_temp("biwu/perform_time")<8+random(3))
	 	{
			me->start_busy(1+random(2));
			if (target = offensive_target(me))
			{
				message_combatd(HIY"$P��Ҫʹ�����ž��������� $p����׼�����ȷ����ˣ�һ�󼱹���$P��æ���ҡ�\n"NOR,me,target);
				if (!target->is_busy())
					COMBAT_D->do_attack(target,me,target->query_temp("weapon"), 0);
			}
			return 1;
		}
		write("�Ǻǡ�\n");
		me->set_temp("biwu/perform_time",time());
	}
	//�жϿ�ʼ��pfm
/////////add from here/////////////////
  if (sscanf(arg, "%s and %s", arg, and) == 2)
      {
       lvl = me->query_skill("hubo", 1);
       if (! lvl)
       		return notify_fail("��Ҫ��ʲô����Ϊ�Լ�����ͷ���۰���\n");

       if (me->query_skill("qimen-wuxing", 1))
          return notify_fail("����ѧ̫�࣬��ͷ���ң����Է��Ķ��á�\n");
       if (lvl <= 100)
          return notify_fail("������һ�����Ϊ̫ǳ�����Է��Ķ��á�\n");
       if (! me->is_fighting())
          return notify_fail("ֻ��ս���в���ʩչ���һ�����\n");
       if (lvl < 250 && random(lvl) < 70)
          {
          me->start_busy(2);
          message_combatd("$N��ͼ���Ķ��ã������־��ǲ���ʹ����\n",me);
          return 1;
          }
       }
       result = do_perform(me, arg);//��һ��pfm
	if (me->query_temp("murong/xingyi")) me->delete_temp("murong/xingyi");
       if (! and || (me->query("int")>=25 && random(lvl)<150))
            return result; //���û�еڶ��� ��ô����
        if (! result)
//						write(me->query_temp("notify_fail"));
//���� û��query_notify_fail()�������  ֻ�����Լ���������
				  message_combatd(HIY"$N��ʽδ�ϣ����ζ�ת����Ȼ���С�\n\n"NOR, me);
        else
        {
          switch (random(4))
          	    {
               case 0:
                        msg += HIY "$N" HIY "���һ����˫�ַ�"
                              "ʹ���У�һ�𹥳���\n" NOR;
                        break;

                case 1:
                        msg += HIY "$N" HIY "˫���������ʹ��"
                              "ͬ��ʽ�������ۻ����ҡ�\n" NOR;
                        break;

                case 2:
                        msg += HIY "$N" HIY "�����ַ�ʹ���У�"
                              "����ͣ�ͣ���������ͬʱ������\n" NOR;
                        break;

                case 3:
                        msg += HIY "$N" HIY "����һ�У�����һ"
                              "�У�������·���죬�������Ե͵���\n" NOR;
                        break;
                }
								msg += "\n";
                message_combatd(msg, me);
        }
//from here
//��ô���������ε�busy? 
//        busy = me->query_busy();
//        me->interrupt_busy(0);
//        if (intp(busy) && intp(me->query_busy()) &&
//            busy > me->query_busy())
//        {
//                me->interrupt_busy(0);
//               me->start_busy();
//       }
        result = do_perform(me, and); //���ڶ���pfm
	if (me->query_temp("murong/xingyi")) me->delete_temp("murong/xingyi");
				return result;
//        if (! result)
//						return 0;
//                write(query_notify_fail());

//        return 1;
/////////add finish///////////////
}
private int do_perform(object me, string arg)
{	
	object weapon, target;
	string martial, skill,pfarg, uarg, parg;
	int result,i,j,ap,dp,plvl,xlvl;

	object tweapon;
	mapping skl, pre_skl;
	string *sskl, *file, skname, sktype, skpf, msg;
	target = offensive_target(me);
	if( sscanf(arg, "%s.%s", martial, arg)!=2 )
	{
		if( weapon = me->query_temp("weapon") )
			martial = weapon->query("skill_type");
		else martial = "unarmed";
	}
/*
	if ( userp(me) )
	     if( !wizardp(me) )
	{
		if( sscanf(arg, "%s %s", parg, uarg)==2 )
		{
			pfarg = "perform/" + parg;
			if( me->query(pfarg,1)<1 )
				return notify_fail("�������������������������������⹦��\n");
		}
//		else if( sscanf(arg, "%s.%s", martial, parg)==2 )
//		{
//			pfarg = "perform/" + parg;
//			if( me->query(pfarg,1)<1 )
//				return notify_fail("�������������������������������⹦��\n");			
//		}
		else 
		{
			pfarg = "perform/" + arg;
			if( me->query(pfarg,1)<1 )
				return notify_fail("��������������������������������"+arg+"��\n");
		}		
	}*/
	if (!stringp(me->query_skill_mapped("force")))
		return notify_fail("û���κ��ڹ���Ϊ�������Ƿ��Ӳ�����ʽ�����ġ�\n");
	if( martial == "parry" && arg != "xingyi")
		return notify_fail( "�����û����мܳ����⹦��\n");
	if( !me->query_temp("weapon") && martial!="unarmed" &&
		martial!="parry" && martial!="dodge")
	{
		pre_skl = me->query_skill_prepare();
		if( !pre_skl ) 
			return notify_fail( "������ prepare ָ��׼����Ҫʹ�õ��⹦��\n");
		else
		{
			sskl = keys(pre_skl);
			j = 0;
			for( i=0; i<sizeof(sskl); i++)
				if( martial == sskl[i]) j=1;
			if( j == 0)
				return notify_fail( "��ֻ��ʹ���Ѿ��� prepare ָ��׼���õ��书���⹦��\n");
		}
	}
/* �������������� */
	if( me->query_temp("lonely-sword/pozhang") && 
	member_array(martial,prep_skl)!=-1 )
			return notify_fail(HIR"����������ˣ�����ʹ���Ͼ���\n"NOR);
	if (arg != "xingyi")
	{
		if( stringp(skill = me->query_skill_mapped(martial)) )
		{
			notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
			if( SKILL_D(skill)->perform_action(me, arg) )
			{
				if( random(120) < (int)me->query_skill(skill) )
					me->improve_skill(skill, 1, 1);
				return 1;
			} else
				if( SKILL_D(martial)->perform_action(me, arg) )
				{
					if( random(120) < (int)me->query_skill(martial, 1) ) me->improve_skill(martial, 1, 1);
					return 1;
				}
				return 0;
		}
		return notify_fail("������ enable ָ��ѡ����Ҫʹ�õ��⹦��\n");
	}
/* ����Ϊ��ת���� */
	else
	{
		me->clean_up_enemy();
		target = me->select_opponent(); 

		if (martial != "parry" ||
			me->query_skill_mapped("parry") != "douzhuan-xingyi")
			return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
		if (me->query("neili") < 500)
			return notify_fail("����������������ʹ�á����ơ���\n");
		plvl = me->query_skill("parry",1);
		if( plvl < 120)
			return notify_fail("�����м�δ���������ܡ����ơ���\n");
		xlvl = me->query_skill("douzhuan-xingyi",1);
		if( xlvl < 120)
			return notify_fail("��ת���Ʋ��������޷������ơ���\n");
		if( me->query_skill("shenyuan-gong",1) < 120)
			return notify_fail("��Ԫ�������죬Ҳ�޷������ơ���\n");
		if( !(me->is_fighting() ))
			return notify_fail("�����ơ�ֻ����ս����ʹ�á�\n");

		target = offensive_target(me);
		if( !target->is_character() )
			return notify_fail("�����һ�㣬�ǲ��������\n");
		if (!living(target) || target->query_temp("noliving") )
			return notify_fail(target->name()+ "�Ѿ�û֪���ˣ����ò��˶Է��������ˡ�\n"); 

		msg = HIG"$N������Ԫ����һ�������Ե����͵�����������\n"NOR;
		message_combatd(msg,me,target);
/* �����б�������ʹ���������perform */
		if( objectp(weapon = me->query_temp("weapon")))
		{
			sktype = weapon->query("skill_type"); 
			if( !objectp(tweapon = target->query_temp("weapon")) ||
				sktype != tweapon->query("skill_type") ) 
					return notify_fail(HIR"���"+target->query("name")+"û�г���ͬ���͵ı�����û�������ơ���\n"NOR); 
			else
			{
				if( me->query_skill(sktype,1) < 120) 
					return notify_fail(HIR"���"+to_chinese(sktype)+"��Ϊ̫ǳ��û��ʹ�á����ơ���\n"NOR); 
				skname = target->query_skill_mapped(sktype);
				if( skname == "murong-sword" ||
					skname == "murong-blade")
					return notify_fail(HIR+target->query("name")+"����Ľ�����ҵĹ�����û��ʹ�á����ơ���\n"NOR); 
				if(!file = get_dir("/kungfu/skill/"+skname+"/"))
					return notify_fail(HIR+target->query("name")+"Ŀǰʹ���书û�о��У�û�������ơ���\n"NOR); 
				skpf = file[random(sizeof(file))];

				ap=random(plvl/2)+xlvl/2;
				dp=target->query_skill("parry") / 2;
				if(dp < 1) dp = 1; 
				if (strsrch(skpf, ".c") >= 0 && ap > dp)
				{
					skpf=replace_string(skpf,".c","");
					msg = HIY "$Nʹ����ת���Ƶľ���"HIR"  �����ơ�  "HIY"����$n"HIY"��"+to_chinese(skname)+"�ľ��и��졢���ݵس��֣�\n"NOR;
					message_combatd(msg, me, target);
/* ���Ƶı�־ */
					me->set_temp("murong/xingyi", 1);
					if( SKILL_D(skname)->perform_action(me, skpf) )
					{
						result = 1;
//						me->start_busy(random(2)+1);
					}
					else
					{
						result = 0;
						msg = HIG"$Nһʱû׽����$n����ʱ���������ڣ�ʹ�������ơ������˿մ���\n"NOR;
						message_combatd(msg,me,target);
					}
					me->delete_temp("murong/xingyi");
				}
				else
				{
					result = 1;
					msg = HIG"$N������ת��˳��һʱ�޷�ʹ�������ơ���\n"NOR;
					message_combatd(msg,me,target);
				}
				return result;
			}
		}
		else
/* ��û�б��� */
		{
			if( objectp(tweapon = target->query_temp("weapon")))
				return notify_fail(HIR"���"+target->query("name")+"û�г���ͬ���͵ı�����û�������ơ���\n"NOR); 
			else
			{
				if( !mapp(pre_skl = target->query_skill_prepare()) || !sizeof(pre_skl))
					sktype = "unarmed";
  			else sktype = keys(pre_skl)[random(sizeof(pre_skl))];
				
				if( me->query_skill(sktype, 1) < 120) 
					return notify_fail(HIR"���"+to_chinese(sktype)+"��Ϊ̫ǳ��û��ʹ�á����ơ���\n"NOR); 

				skname = target->query_skill_mapped(sktype);
				if( skname == "xingyi-strike" ||
					skname == "canhe-finger")
					return notify_fail(HIR+target->query("name")+"����Ľ�����ҵĹ�����û��ʹ�á����ơ���\n"NOR); 
/* �Է�ͽ��û��perform */
				if(!file = get_dir("/kungfu/skill/"+skname+"/"))
				{
					msg = HIG"$N����ת���ƣ����������ӿ죬���ֶ�Ȼ�ӿ죡���أ���\n"NOR;
					message_combatd(msg,me,target);
					me->add_temp("apply/attack", 20);
					me->add_temp("apply/dodge", 10);
					me->add_temp("apply/defense", 10);
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
					me->add_temp("apply/attack", -20);
					me->add_temp("apply/dodge", -10);
					me->add_temp("apply/defense", -10);
					me->start_busy(random(3)+1);
					return 1;
				}
				skpf = file[random(sizeof(file))];

				ap=random(plvl/2)+xlvl/2;
				dp=target->query_skill("parry") / 2;
				if(dp < 1) dp = 1; 
				if (strsrch(skpf, ".c") >= 0 && ap > dp)
				{
					skpf=replace_string(skpf,".c","");
					msg = HIY "$Nʹ����ת���Ƶľ���"HIR"  �����ơ�  "HIY"����$n��"+to_chinese(skname)+"�ľ��и��졢���ݵس��֣�\n"NOR;
					message_combatd(msg, me, target);
/* ���Ƶı�־ */
					me->set_temp("murong/xingyi", 1);
					if( SKILL_D(skname)->perform_action(me, skpf) )
					{
						result = 1;
//						me->start_busy(random(2)+1);
					}
					else
					{						
						result = 0;
						msg = HIG"$Nһʱû׽����$n����ʱ���������ڣ�ʹ�������ơ������˿մ���\n"NOR;
						message_combatd(msg,me,target);
						return 0;
					}
					me->delete_temp("murong/xingyi");
				}
				else
				{
					result = 1;
					msg = HIG"$N������ת��˳��һʱ�޷�ʹ�������ơ���\n"NOR;
					message_combatd(msg,me,target);
				}
				return result;
			}
		}
		me->start_busy(random(2)+1);
		me->delete_temp("murong/xingyi");
		return 1;
	}
}
int help (object me)
{
	write(@HELP
ָ���ʽ��perfrom | yong [<�书����>.]<��ʽ����> [<ʩ�ö���>]
          perform | yong ��ʽ1 [<����1>] and ��ʽ2 [<����2>]

    �������ѧ���⹦��ȭ�š�����������....����һЩ����Ĺ�����
ʽ����ʽ�����������ָ����ʹ�ã���������� enable ָ��ָ����ʹ
�õ��书����ָ���书����ʱ�����ֵ��⹦��ָ���ȭ�Ź���ʹ����
��ʱ���Ǳ��е��书�������⹦��ʩչ��������׼���� ��prepare����
�ļ��ܡ��е��ر���⹦���Լ�����Ӧ����Ϊparry��ʩչ��

    ��������⹦�������಻ͬ��������ʽ������ͬ�ģ����߲����ȭ
�Ÿ��������ܵ��书(���Ṧ)�������� <�书>.<��ʽ>  �ķ�ʽָ����
�磺

    perform sword.chan
    perform sword.chan and sword.lian

    ���仰˵��ֻҪ�� enable �е��书��������ʽ�ģ������������
ָ��ʹ�á��ܶ��书�����⹥�������ǳ�������һ��ʹ�ã������¶Է�
��ƴ������������˵�������������Զ���ʼ������㡣����Ҫ����ʹ
��Ŷ:)��

����㾫ͨ���һ���������ͬʱʹ��������ʽ����ͬһ���ֻ���ֱ�
�������ˡ����һ���������Խ�Ǿ����ɹ���Խ�ߡ�

HELP
	);
	return 1;
}