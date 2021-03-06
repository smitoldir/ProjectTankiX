#include <gamebase/Gamebase.h>
using namespace gamebase;
using namespace std;
#include "heads\CrewAndModules.h"
#include"heads\Tanks.h"
#include"heads\Maths.h"
#include"heads\Level.h"
#include <thread>


//

int stepn = 100;
int game = 0;


class MyApp : public App
{
	void play()
	{
		game = 1;
		stolb1.hide();
		blk.hide();
	}
	
	void stopgame()
	{
		stolb1.show();
		blk.show();
		game = 0;
	}

	////////////////////////////////////////////// //////////////////////////////////////////////

    void load()
    {
		audio.loop("ostTrek.ogg");
		audio.loop("dviglo.ogg", 1);
		randomize();
        mainhsangle = 0;
        //auto tvec = Vec2(10.0, 0.0);
        //tvec.rotate(mainhs.angle());
        //maint.setPos(tvec + mainhs.pos());
        angar.setPos(angar.pos() + Vec2(300.0, 200.0));
        kishki_angara.setPos(Vec2(300.0, 200.0));
        wall1.setPos(angar.pos() + Vec2(0.0, 63.0));
        wall2.setPos(angar.pos() + Vec2(0.0, -63.0));
        tower = 0;
        gun = 0;
        housingm = 0;
        Acom = 0;
        Azar = 0;
        Araddist = 0;
        Amesh_vod = 0;
        Anavod = 0;

        tankData(gddos,tddos,hsddos);
		kpk.hide();
        ///////////////////////////////// "��������� �������� ������"

        maing = guns.load("g1.json");
        maint = towers.load("t1.json");
        mainhs = housing.load("hs1.json");
        mainhs.setAngle(mainhsangle);
        mainhs.setPos(500, 0);

        //////////////////////////////// "��������� �������� ����������"

        animg = guns.load("g1.json");
        animt = towers.load("t1.json");
        animhs = housing.load("hs1.json");
        mainbhbphspbhbp = bhbp.load("hpb.json");
        animbhbphspbhbp = bhbp.load("hpb.json");

        mainhp = hsddos[housingm].hp;
        myhp = hsddos[animhs].hp;

        animhsangle = 0;
        Atower = 0;
        Agun = 0;
        Ahousing = 0;
        gusliy = 0;
        dviglo = 0;
        bashnia = 0;
        triplex = 0;
        dulo = 0;
        bk = 0;
        radio = 0;


        auto tvec = Vec2(10.0, 0.0);
        tvec.rotate(animhs.angle());
        maint.setPos(tvec + mainhs.pos());

        auto atvec = Vec2(10.0, 0.0);
        //atvec.rotate(animhs.angle());
        animt.setPos(atvec + animhs.pos());

        auto gvec = gddos[gun].sg;
        gvec.rotate(animt.angle());
        maing.setPos(gvec + maint.pos());

        auto agvec = gddos[gun].sg;
        agvec.rotate(animt.angle());
        animg.setPos(agvec + animt.pos());

        rload.setScaleX(0);


        /////������
        connect(newgame, play);
        connect(exit, close);

        //////////////////////////////////////////////������������� �����/////////////////////////////////////
        levelGen(clay, shaders1, baricades);
    
    }

	////////////////////////////////////////////////////////////////////////////////////////////

	void process(Input input)
	{
		//�������� ���������� ������ ����
		if (game == 0)
			return;

		//////////////////////////////////////////////����������//////////////////////////////////////////////
		using namespace InputKey;
        kishki_angara.hide();
        
		ratio = (mainhp) / (hsddos[housingm].hp);
		myratio = (myhp) / (hsddos[animhs].hp);
		auto angvec = mainhs.pos() - animt.pos();
		if (myhp <= 0)
			myhp = 0;
		if (mainhp <= 0)
			mainhp = 0;
		
        auto uskr = hsddos[housingm].uskr;
		auto spvec = Vec2(hsddos[housingm].hsspeed, 0.0);
		//auto tormvec = Vec2(hsddos[housingm].uskr, 0.0);
		spvec.rotate(mainhsangle);
		//tormvec.rotate(mainhsangle);
		//-------------------------���������� �������

		/*if (dulo == 1)
		{
			gddos[gun].gload * 2;
		}
		*/
        mainhs.move(spidomer * timeDelta());
        maint.move(spidomer * timeDelta());
        maing.move(spidomer * timeDelta());


		//-------------------------������
		if (input.pressed(W) && (dviglo != 2) && (mesh_vod != 2))
        {
            //spidomer += tormvec;
            spidomer += (polarVec(uskr, mainhs.angle()))*timeDelta();
			if (spidomer.length() > hsddos[housingm].hsspeed)
				spidomer = (polarVec(hsddos[housingm].hsspeed, mainhs.angle()));
			
			if (mainhs.box().intersects(wall1.box()) || mainhs.box().intersects(wall2.box()))
			{
                kishki_angara.show();
                angar.hide();
             
				mainhs.setPos(mainhs.pos() - spidomer * timeDelta());
				maint.setPos(maint.pos() - spidomer * timeDelta());
				maing.setPos(maing.pos() - spidomer * timeDelta());
                spidomer = Vec2(0, 0);
			}
            else
            {
                kishki_angara.hide();
                angar.show();
            }
		}
		//---------------------------------�����
		if (input.pressed(S) && (dviglo != 2) && (mesh_vod != 2))
		{
            spidomer -= (polarVec(uskr, mainhs.angle()))*timeDelta();
			if (spidomer.length() > hsddos[housingm].hsspeed)
				spidomer = (polarVec(hsddos[housingm].hsspeed, mainhs.angle()-3.14));
			if (mainhs.box().intersects(wall1.box()) || mainhs.box().intersects(wall2.box()))
			{
                kishki_angara.show();
                angar.hide();
				mainhs.setPos(mainhs.pos() + spvec * timeDelta());
				maint.setPos(maint.pos() + spvec * timeDelta());
				maing.setPos(maing.pos() + spvec * timeDelta());
			}
            else
            {
                kishki_angara.hide();
                angar.show();
            }
		}
		
        if (mainhs.box().intersects(angar.box()))
        {
            kishki_angara.show();
            angar.hide();
        }
        else
        {
            kishki_angara.hide();
            angar.show();
        }

        if (!input.pressed(W) && !input.pressed(S))
        {
            if (spidomer.length() > 0)
            {
                spidomer -= spidomer*timeDelta();
            }
			if (spidomer.length() <= 10)
				spidomer = Vec2(0,0);
        }
        duster.setPeriod(20/(spidomer.length()));
        if (!spidomer.length() <= 0)
        {
            
            if (duster.check())
            {
				
                auto ddust = dust.load("dust.json", mainhs.pos());
                ddust.anim.run("zatux");
                dust.data(ddust) = spidomer/1.25;
				
				for (auto clay1 : clay.all())
				{
					if (!clay.find(mainhs.box()).empty())
					{
						auto ttrakiLight = traki.load("sledLight.json", mainhs.pos());
						ttrakiLight.anim.run("slzat");
						ttrakiLight.setAngle(spidomer.angle());
					}
					else
					{
						auto ttraki = traki.load("sled.json", mainhs.pos());
						ttraki.anim.run("slzat");
						ttraki.setAngle(spidomer.angle());
					}
				}
            }
        }
        for (auto ddust : dust.all())
            ddust.move(dust.data(ddust)*timeDelta());
       
		//------------------------------------�����
		if (input.pressed(A)&& (dviglo !=2) && (mesh_vod != 2))
		{
			if (spidomer.length() > 0)
			{
				spidomer -= spidomer*timeDelta();
			}

			auto tvec = Vec2(10.0, 0.0);
			mainhsangle += 3.14 * timeDelta();
			mainhs.setAngle(mainhsangle);
			tvec.rotate(mainhs.angle());
			maint.setPos(tvec + mainhs.pos());
			auto gvec = gddos[gun].sg + tddos[tower].sgt;
			gvec.rotate(maint.angle());
			maing.setPos(gvec + maint.pos());
			if (mainhs.box().intersects(wall1.box()) || mainhs.box().intersects(wall2.box()))
			{
				auto tvec = Vec2(10.0, 0.0);
				mainhsangle -= 3.14 * timeDelta();
				mainhs.setAngle(mainhsangle);
				tvec.rotate(mainhs.angle());
				maint.setPos(tvec + mainhs.pos());
				auto gvec = gddos[gun].sg + tddos[tower].sgt;
				gvec.rotate(maint.angle());
				maing.setPos(gvec + maint.pos());
			}
		}
		//-------------------------------------������
		if (input.pressed(D) && (dviglo != 2) && (mesh_vod != 2))
		{
			if (spidomer.length() > 0)
			{
				spidomer -= spidomer*timeDelta();
			}
			auto tvec = Vec2(10.0, 0.0);
			mainhsangle -= 3.14 * timeDelta();
			mainhs.setAngle(mainhsangle);
			tvec.rotate(mainhs.angle());
			maint.setPos(tvec + mainhs.pos());
			auto gvec = gddos[gun].sg + tddos[tower].sgt;
			gvec.rotate(maint.angle());
			maing.setPos(gvec + maint.pos());
			if (mainhs.box().intersects(wall1.box()) || mainhs.box().intersects(wall2.box()))
			{
				auto tvec = Vec2(10.0, 0.0);
				mainhsangle += 3.14 * timeDelta();
				mainhs.setAngle(mainhsangle);
				tvec.rotate(mainhs.angle());
				maint.setPos(tvec + mainhs.pos());
				auto gvec = gddos[gun].sg + tddos[tower].sgt;
				gvec.rotate(maint.angle());
				maing.setPos(gvec + maint.pos());
			}
		}
		
		//--------------------------------------����� ������
		if ((input.pressed(E) || input.pressed(K))&&((bashnia<2)||(navod<2)))
		{
			maint.setAngle(maint.angle() - tddos[tower].tfov*timeDelta());
			maing.setAngle(maing.angle() - tddos[tower].tfov*timeDelta());
			auto gvec = gddos[gun].sg + tddos[tower].sgt;
			gvec.rotate(maint.angle());
			maing.setPos(gvec + maint.pos());
		}

		//---------------------------------------����� �����
		if ((input.pressed(Q) || input.pressed(J)) && ((bashnia<2) || (navod<2)))
		{
			maint.setAngle(maint.angle() + tddos[tower].tfov*timeDelta());
			maing.setAngle(maing.angle() + tddos[tower].tfov*timeDelta());
			auto gvec = gddos[gun].sg + tddos[tower].sgt;
			gvec.rotate(maint.angle());
			maing.setPos(gvec + maint.pos());
		}
		/*
		if (maint.angle() > 6.28)
		maint.setAngle(0); 
		//	if (maint.angle() == -3.14)
		//		maint.setAngle(3.14);
		*/

		//-----------------------------------�������
		if ((input.pressed(Space)) && (shellTimer.time() > gddos[gun].gload) && ((dulo != 2) || (zar<2)))
		{
			shellTimer.start();
			auto shellCreate = shaders2.load("shell.json");
			shellCreate.setAngle(maing.angle());
			shellCreate.setPos(maing.pos());
			if (gun == 1)
				audio.run("vystrel-i-padaet-gilza_(mp3-CC.com).ogg");
			//rload.setSizes(gddos[gun].gload/1000*timeDelta(), 20);
		}
		//-----------------------------------���

		if (input.justPressed(M))
		{
			if (kpk.isVisible())
			{
				kpk.hide();
			}
			else
			{
				kpk.show();
			}
		}
		if ((input.pressed(W)) || (input.pressed(S)) || (input.pressed(A)) || (input.pressed(D)))
		{
			audio.resume(1);
		}
		else
		audio.pause(1);
		//-----------------------------------�����
		if (input.pressed(Escape))
		{
			stopgame();
		}
		
		//�����������
		rtm = shellTimer.time() / gddos[gun].gload;
		if (rtm >= 1)
			rtm = 1;
		rload.setScaleX(rtm);

		/*
		if(input.pressed('�'))
		{
		ag1 = mainhs.angle() - maint.angle() + 3.14;
		if (ag1 < 3.14)
		{
		maint.setAngle(maint.angle() + 3.14 * timeDelta());
		maing.setAngle(maint.angle() + 3.14 * timeDelta());
		auto gvec = Vec2(47.0, -5.0);
		gvec.rotate(maint.angle());
		maing.setPos(gvec + maint.pos());
		}
		if (ag1 > 3.14)
		{
		maint.setAngle(maint.angle() - 3.14 * timeDelta());
		maing.setAngle(maint.angle() - 3.14 * timeDelta());
		auto gvec = Vec2(47.0, -5.0);
		gvec.rotate(maint.angle());
		maing.setPos(gvec + maint.pos());
		}
		}
		*/

		for (auto shell : shaders2.all())
		{
			auto vecsh = Vec2(2000.0, 0.0);
			vecsh.rotate(shell.angle());
			shell.setPos(shell.pos() + vecsh* timeDelta());
			if (!shell.box().intersects(Box(-10000, -10000, 10000, 10000)))
			{
				shaders2.remove(shell);
				continue;
			}
			if (dist(shell.pos(), animhs.pos()) <= hsddos[Ahousing].diameter / 2)
			{
				mainhp -= gddos[gun].uron; \
					if (mainhp <= 0)
					{
						auto Explosion = shaders1.load("explosion.json");
						Explosion.setPos(animhs.pos());
						Explosion.anim.run("expl");
						Adestroed = true;
						shaders2.remove(shell);
						continue;
					}
			}
			else
			{
				auto sdvigvec = Vec2(hsddos[Ahousing].sdvig, 0.0);
				sdvigvec.rotate(animhsangle);
				if (dist(shell.pos(), animhs.pos() + sdvigvec) <= hsddos[Ahousing].diameter / 2)
				{
					mainhp -= gddos[gun].uron * 2;
					if (mainhp <= 0)
					{
						auto Explosion = shaders1.load("explosion.json");
						Explosion.setPos(animhs.pos());
						Explosion.anim.run("expl");
						Adestroed = true;
						shaders2.remove(shell);
						continue;
					}
				}
				else
				{
					if (dist(shell.pos(), animhs.pos() - sdvigvec) <= hsddos[Ahousing].diameter / 2)
					{
						mainhp -= gddos[gun].uron * 3;
						if (mainhp <= 0)
						{
							auto Explosion = shaders1.load("explosion.json");
							Explosion.setPos(animhs.pos());
							Explosion.anim.run("expl");
							Adestroed = true;
							shaders2.remove(shell);
							continue;
						}
					}
					if (shell.box().intersects(wall1.box()) || shell.box().intersects(wall2.box()))
						shaders2.remove(shell);
				}
			}
		}

		//-----------------------------------------------����� ������

		if (input.justPressed('1') && gun != 0)
		{
			gun--;
			auto angel = maing.angle();
			guns.remove(maing);
			maing = guns.load(gddos[gun].nameg);
			maing.setAngle(angel);

			auto gvec = gddos[gun].sg + tddos[tower].sgt;
			gvec.rotate(maint.angle());
			maing.setPos(gvec + maint.pos());
		}
		if (input.justPressed('2') && gun != 4)
		{
			gun++;
			auto angel = maing.angle();
			guns.remove(maing);
			maing = guns.load(gddos[gun].nameg);
			maing.setAngle(angel);
			auto gvec = gddos[gun].sg + tddos[tower].sgt;
			gvec.rotate(maint.angle());
			maing.setPos(gvec + maint.pos());
		}

		if (input.justPressed('3') && tower != 0)
		{
			tower--;
			auto angel = maint.angle();
			towers.remove(maint);
			maint = towers.load(tddos[tower].namet);
			maint.setAngle(angel);

			auto tvec = Vec2(10.0, 0.0);
			tvec.rotate(mainhs.angle());
			maint.setPos(tvec + mainhs.pos());
			auto gvec = gddos[gun].sg + tddos[tower].sgt;
			gvec.rotate(maint.angle());
			maing.setPos(gvec + maint.pos());
		}
		if (input.justPressed('4') && tower != 4)
		{
			tower++;
			auto angel = maint.angle();
			towers.remove(maint);
			maint = towers.load(tddos[tower].namet);
			maint.setAngle(angel);

			auto tvec = Vec2(10.0, 0.0);
			tvec.rotate(mainhs.angle());
			maint.setPos(tvec + mainhs.pos());
			auto gvec = gddos[gun].sg + tddos[tower].sgt;
			gvec.rotate(maint.angle());
			maing.setPos(gvec + maint.pos());
		}

		if (input.justPressed('5') && housingm != 0)
		{
			housingm--;
			auto hspos = mainhs.pos();
			auto angel = mainhs.angle();
			housing.remove(mainhs);
			mainhs = housing.load(hsddos[housingm].namehs);
			mainhs.setAngle(angel);
			mainhs.setPos(hspos);

			myhp = hsddos[housingm].hp;
		}
		if (input.justPressed('6') && housingm != 5)
		{
			housingm++;
			auto hspos = mainhs.pos();
			auto angel = mainhs.angle();
			housing.remove(mainhs);
			mainhs = housing.load(hsddos[housingm].namehs);
			mainhs.setAngle(angel);
			mainhs.setPos(hspos);

			myhp = hsddos[housingm].hp;
		}
		if (destroed == true)
		{
			auto hspos = mainhs.pos();
			auto angel = mainhs.angle();
			housing.remove(mainhs);
			mainhs = housing.load(hsddos[housingm].dnamehs);
			mainhs.setAngle(angel);
			mainhs.setPos(hspos);

			auto angelt = maint.angle();
			towers.remove(maint);
			maint = towers.load(tddos[tower].dnamet);
			maint.setAngle(angelt);

			auto tvec = Vec2(10.0, 0.0);
			tvec.rotate(mainhs.angle());
			maint.setPos(tvec + mainhs.pos());
			auto gvec = gddos[gun].sg + tddos[tower].sgt;
			gvec.rotate(maint.angle());
			maing.setPos(gvec + maint.pos());

			auto angelg = maing.angle();
			guns.remove(maing);
			maing = guns.load(gddos[gun].dnameg);
			maing.setAngle(angelg);
			auto ggvec = gddos[gun].sg + tddos[tower].sgt;
			ggvec.rotate(maint.angle());
			maing.setPos(gvec + maint.pos());
		}
		if (Adestroed == true)
		{
			auto hspos = animhs.pos();
			auto angel = animhs.angle();
			housing.remove(animhs);
			animhs = housing.load(hsddos[Ahousing].dnamehs);
			animhs.setAngle(angel);
			animhs.setPos(hspos);

			auto angelt = animt.angle();
			towers.remove(animt);
			animt = towers.load(tddos[Atower].dnamet);
			animt.setAngle(angelt);

			auto tvec = Vec2(10.0, 0.0);
			tvec.rotate(animhs.angle());
			animt.setPos(tvec + animhs.pos());
			auto gvec = gddos[Agun].sg + tddos[Atower].sgt;
			gvec.rotate(animt.angle());
			animg.setPos(gvec + animt.pos());

			auto angelg = animg.angle();
			guns.remove(animg);
			animg = guns.load(gddos[Agun].dnameg);
			animg.setAngle(angelg);
			auto ggvec = gddos[Agun].sg + tddos[Atower].sgt;
			ggvec.rotate(animt.angle());
			animg.setPos(gvec + animt.pos());
		}
		//cout << animt.angle() << " -> " << angvec.angle() << endl;
        OurCrewModules(bk, com, raddist, zar, mesh_vod, navod, dviglo, radio ,triplex, gusliy, bashnia, dulo , mainbhbphspbhbp);

		

		//////////////////////////////////////////////���������/////////////////////////////////////////////


		if (AshellTimer.time() > gddos[Agun].gload)
		{
			AshellTimer.start();
			auto shellCreate = shaders2.load("shell.json");
			shellCreate.setAngle(animg.angle());
			shellCreate.setPos(animg.pos());

			//rload.setSizes(gddos[Agun].gload/1000*timeDelta(), 20);
		}


		/*
		if(input.pressed('�'))
		{
		ag1 = mainhs.angle() - maint.angle() + 3.14;
		if (ag1 < 3.14)
		{
		maint.setAngle(maint.angle() + 3.14 * timeDelta());
		maing.setAngle(maint.angle() + 3.14 * timeDelta());
		auto gvec = Vec2(47.0, -5.0);
		gvec.rotate(maint.angle());
		maing.setPos(gvec + maint.pos());
		}
		if (ag1 > 3.14)
		{
		maint.setAngle(maint.angle() - 3.14 * timeDelta());
		maing.setAngle(maint.angle() - 3.14 * timeDelta());
		auto gvec = Vec2(47.0, -5.0);
		gvec.rotate(maint.angle());
		maing.setPos(gvec + maint.pos());
		}
		}
		*/

		/*
		if( tower==0)
		{
		if( gun=1)
		{
		guns.clear();
		guns.add(loadObj <GameObj> ("g1"));
		sg = Vec2(32.0, 0.0);
		g1.setPos(t1.pos);
		sg.setAngle(t1);
		g1.setPos(g1.pos+sg*timeDelta());

		}
		}
		*/

		mainbhbphspbhbp.setPos(mainhs.pos().x, mainhs.pos().y + 50);
		mainbhbphspbhbp.child<GameObj>("hpb").setScaleX(myratio);
		animbhbphspbhbp.setPos(animhs.pos().x, animhs.pos().y + 50);
		animbhbphspbhbp.child<GameObj>("hpb").setScaleX(ratio);
		gamepole.setView(mainhs.pos());

        TheirCrewModules(Abk, Acom, Araddist, Azar, Amesh_vod, Anavod, Adviglo, Aradio, Atriplex, Agusliy, Abashnia, Adulo, animbhbphspbhbp);
		
        animbhbphspbhbp.child<Layout>("Row2").update();
		////////////////////////////////////////////////////////////////////////////////////////////
		
	}
	

	//////////////////////////////////////////////������ ��������//////////////////////////////////////////////
	void moveShells()
	{
		for (auto shell : shaders2.all())
		{
			auto vecsh = Vec2(200.0, 0.0);
			vecsh.rotate(shell.angle());
            shaders2.data(shell) = shell.pos();
			shell.setPos(shell.pos() + vecsh / stepn * timeDelta());

            if (VecIntersection(shaders2, mainhs, shell))
            {
                gusliy++;
            }

				
			if (!shell.box().intersects(Box(-10000,-10000, 10000, 10000)))
			{
				shaders2.remove(shell);
				continue;
			}
			if (dist(shell.pos(), animhs.pos()) <= hsddos[Ahousing].diameter / 2)
			{
				int a = 0;
				shaders2.remove(shell);
				mainhp -= gddos[gun].uron;
				
				a = randomInt(1, 2);
				if ((a == 2) && (Aradio<2))
					Aradio++;
				continue;
			}
			else
			{
				auto sdvigvec = Vec2(hsddos[Ahousing].sdvig, 0.0);
				sdvigvec.rotate(animhsangle);
				if (dist(shell.pos(), animhs.pos() + sdvigvec) <= hsddos[Ahousing].diameter / 2)
				{
					
					shaders2.remove(shell);
					mainhp -= gddos[gun].uron * 2;
					
					for (int aa = 1; aa != 0;)
					{
						int a = 0;
						aa = 0;
						a = randomInt(1, 2);

						if ((a == 1) && (Araddist < 2))
							Araddist++;
						if ((a == 2) && (Amesh_vod < 2))
							Amesh_vod++;
						if ((Araddist == 2) && (Amesh_vod == 2))
							break;
					}
					
					
					for (int aa = 1; aa != 0;)
					{
						int a = 0;
						aa = 0;
						a = randomInt(1, 4);

						if ((a == 1) && (Abk < 2))
							Abk++;
						if ((a == 2) && (Adulo < 2))
							Adulo++;
						if ((a == 3) && (Atriplex < 2))
							Atriplex++;
						if ((a == 4) && (Abashnia < 2))
							Abashnia++;

						if ((a == 1) && (Abk == 2))
							aa++;
						if ((a == 2) && (Adulo == 2))
							aa++;
						if ((a == 3) && (Atriplex == 2))
							aa++;
						if ((a == 4) && (Abashnia == 2))
							aa++;
						if ((Abk == 2) && (Adulo == 2) && (Atriplex == 2) && (Abashnia == 2))
						break;
					}
					for (int aa = 1; aa != 0;)
					{
						int a = 0;
						aa = 0;
						a = randomInt(1, 2);

						if ((a == 1) && (Acom < 2))
							Acom++;
						if ((a == 2) && (Azar < 2))
							Azar++;
						if ((a == 2) && (Anavod < 2))
							Anavod++;
						if ((Anavod == 2) && (Azar == 2) && (Acom == 2))
							break;
					}
					continue;
				}
				else
				{
					if (dist(shell.pos(), animhs.pos() - sdvigvec) <= hsddos[Ahousing].diameter / 2)
					{
						
						shaders2.remove(shell);
						mainhp -= gddos[gun].uron * 3;
						
					
						if (Adviglo<2)
							Adviglo++;
						continue;
					}
					if (shell.box().intersects(wall1.box()) || shell.box().intersects(wall2.box()))
					{
						shaders2.remove(shell);
						continue;
					}
				}
			}
			if (dist(shell.pos(), mainhs.pos()) <= hsddos[housingm].diameter / 2)
			{
				int aa = 0;
				shaders2.remove(shell);
				myhp -= gddos[Agun].uron;
				if (myhp <= 0)
				{
					auto Explosion = shaders1.load("explosion.json");
					Explosion.setPos(mainhs.pos());
					Explosion.anim.run("expl");
					destroed = true;
				}
				aa = randomInt(1, 2);
				if ((aa == 2) && (radio<2))
					radio++;
				if ((aa == 1) && (raddist < 2))
					raddist++;
				if ((aa == 2) && (mesh_vod < 2))
					mesh_vod++;
				if ((raddist == 2) && (mesh_vod == 2))
					break;
				continue;
			}
			else
			{
				auto sdvigvec = Vec2(hsddos[Ahousing].sdvig, 0.0);
				sdvigvec.rotate(animhsangle);
				if (dist(shell.pos(), mainhs.pos() + sdvigvec) <= hsddos[housingm].diameter / 2)
				{
					
					shaders2.remove(shell);
					myhp -= gddos[Agun].uron * 2;
					if (myhp <= 0)
					{
						auto Explosion = shaders1.load("explosion.json");
						Explosion.setPos(mainhs.pos());
						Explosion.anim.run("expl");
						destroed = true;
						
					}
					for (int aa = 1; aa != 0;)
					{
						int a = 0;
						aa = 0;
					a = randomInt(1, 4);
					if ((a == 1) && (bk<2))
						bk++;
					if ((a == 2) && (dulo<2))
						dulo++;
					if ((a == 3) && (triplex<2))
						triplex++;
					if ((a == 4) && (bashnia < 2))
						bashnia++;

					if ((a == 1) && (bk == 2))
						aa++;
					if ((a == 2) && (dulo == 2))
						aa++;
					if ((a == 3) && (triplex == 2))
						aa++;
					if ((a == 4) && (bashnia == 2))
						aa++;
					if ((bk == 2) && (dulo == 2) && (triplex == 2) && (bashnia == 2))
						break;
						for (int aa = 1; aa != 0;)
						{
							int a = 0;
							aa = 0;
							a = randomInt(1, 2);

							if ((a == 1) && (com < 2))
								com++;
							if ((a == 2) && (zar < 2))
								zar++;
							if ((a == 2) && (navod < 2))
								navod++;
							if ((navod == 2) && (zar == 2) && (com == 2))
								break;
						}
					continue;
				}
					continue;
				}
				else
				{
					if (dist(shell.pos(), mainhs.pos() - sdvigvec) <= hsddos[housingm].diameter / 2)
					{
						
						shaders2.remove(shell);
						myhp -= gddos[Agun].uron * 3;
						if (myhp <= 0)
						{
							auto Explosion = shaders1.load("explosion.json");
							Explosion.setPos(mainhs.pos());
							Explosion.anim.run("expl");
							destroed = true;
						
						}
						if (dviglo<2)
							dviglo++;
						continue;
					}
					if (shell.box().intersects(wall1.box()) || shell.box().intersects(wall2.box()))
					{
						shaders2.remove(shell);
						continue;
					}
				}
			}
		}


		for (auto shell : shaders2.all())
		{
			for (auto house : baricades.all())
			{
				if (shell.box().intersects(around(32, 32, house.pos() + Vec2(16, 16))))
				{
					house.child<Texture>("roof1").hide();
					shell.kill();
					break;
				}
				if (shell.box().intersects(around(32, 32, house.pos() + Vec2(-16, 16))))
				{
					house.child<Texture>("roof2").hide();
					shell.kill();
					break;
				}
				if (shell.box().intersects(around(32, 32, house.pos() + Vec2(-16, -16))))
				{
					house.child<Texture>("roof3").hide();
					shell.kill();
					break;
				}
				if (shell.box().intersects(around(32, 32, house.pos() + Vec2(16, -16))))
				{
					house.child<Texture>("roof4").hide();
					shell.kill();
					break;
				}
			}
		}
	}
	//////////////////////////////////////////////�������� ����������//////////////////////////////////////////////
	void moveAnim()
	{
		auto angvec = mainhs.pos() - animt.pos();
		if (dist(mainhs.pos(), animhs.pos()) > 400 && (Adviglo != 2))
		{
			auto spvec = Vec2(hsddos[Ahousing].hsspeed, 0.0);
			spvec.rotate(animhsangle);
			animhs.setPos(animhs.pos() + spvec * timeDelta());
			animt.setPos(animt.pos() + spvec * timeDelta());
			animg.setPos(animg.pos() + spvec * timeDelta());
			auto deltaGrad= abs(animhs.angle() - angvec.angle());
			bool vuchisl = false;
			if (deltaGrad > 3.1415926535897932384626433832795)
			{
				deltaGrad = 2 * 3.1415926535897932384626433832795 -deltaGrad;
				vuchisl = true;
			}
			if (deltaGrad>0.174)
			{
				if ((animhs.angle() < angvec.angle()&& (!vuchisl))|| (animhs.angle() > angvec.angle() && (vuchisl)))
				{

					auto tvec = Vec2(10.0, 0.0);
					animhsangle += 3.14 * timeDelta();
					animhs.setAngle(animhsangle);
					tvec.rotate(animhs.angle());
					animt.setPos(tvec + animhs.pos());
					auto gvec = gddos[Agun].sg + tddos[Atower].sgt;
					gvec.rotate(animt.angle());
					animg.setPos(gvec + animt.pos());
					if (animt.angle() > 3.1415926535897932384626433832795)
					{
						animt.setAngle(animt.angle() - 2 * 3.1415926535897932384626433832795);
					}
				}
				else
				{
					auto tvec = Vec2(10.0, 0.0);
					animhsangle -= 3.14 * timeDelta();
					animhs.setAngle(animhsangle);
					tvec.rotate(animhs.angle());
					animt.setPos(tvec + animhs.pos());
					auto gvec = gddos[Agun].sg + tddos[Atower].sgt;
					gvec.rotate(animt.angle());
					animg.setPos(gvec + animt.pos());
					if (animt.angle() < -3.1415926535897932384626433832795)
					{
						animt.setAngle(animt.angle() + 2 * 3.1415926535897932384626433832795);
					}
				}
			}
		}

		if (Abashnia!=2)
		{
			auto deltaGrad= abs(animt.angle() - angvec.angle());
			bool vuchisl = false;
			if (deltaGrad > 3.1415926535897932384626433832795)
			{
				deltaGrad = 2 * 3.1415926535897932384626433832795 - deltaGrad;
				vuchisl = true;
			}
			if (deltaGrad > 0.174)
			{
				if ((animt.angle() < angvec.angle() && (!vuchisl))|| (animt.angle() > angvec.angle() && (vuchisl)))
				{
					animt.setAngle(animt.angle() + tddos[Atower].tfov*timeDelta());
					animg.setAngle(animg.angle() + tddos[Atower].tfov*timeDelta());
					auto gvec = gddos[Agun].sg + tddos[Atower].sgt;
					gvec.rotate(animt.angle());

					animg.setPos(gvec + animt.pos());

					if (animt.angle() > 3.1415926535897932384626433832795)
					{
						animt.setAngle(animt.angle() - 2 * 3.1415926535897932384626433832795);
					}
				}
				else
				{
					animt.setAngle(animt.angle() - tddos[Atower].tfov*timeDelta());
					animg.setAngle(animg.angle() - tddos[Atower].tfov*timeDelta());
					auto gvec = gddos[Agun].sg - tddos[Atower].sgt;
					gvec.rotate(animt.angle());
					animg.setPos(gvec + animt.pos());
					if (animt.angle() < -3.1415926535897932384626433832795)
					{
						animt.setAngle(animt.angle() + 2 * 3.1415926535897932384626433832795);
					}
				}
			}
		}
	}

	void move()
	{
		//�������� ���������� ������ ����
		if (game == 0)
			return;
		for(int i=0;i<stepn;i++)
		moveShells();
		moveAnim();

	}

	/*float ag1;
	float tg;
	float rtm;*/

	////////////////////////////////
	LayerFromDesign(void, housing);
    LayerFromDesign(void, shaders1);
	LayerFromDesign(void, baricades);
    LayerFromDesign(void, traki);
    LayerFromDesign(Vec2, dust);
	LayerFromDesign(Vec2, shaders2);
	LayerFromDesign(void, guns);
	LayerFromDesign(void, towers);
	FromDesign(GameObj, rload);
	FromDesign(GameObj, angar);
    FromDesign(GameObj, kishki_angara);
	FromDesign(GameObj, wall1);
	FromDesign(GameObj, wall2);
	////////////////////////////////
    Timer duster;
	//////// ��� ����
	float mainhsangle;
	float animhsangle;
	int tower;
	int gun;
	int housingm;
	float myhp;
	float myratio;
	GameObj mainhs;
	GameObj maint;
	GameObj maing;
	Timer shellTimer;
	float rtm;
    Vec2 spidomer;
	bool destroed;
	///////////////////////������
	int gusliy;
	int dviglo;
	int bashnia;
	int triplex;
	int dulo;
	int bk;
	int radio;
	///////////////////////������
	int com;
	int zar;
	int raddist;
	int mesh_vod;
	int navod;

	//////// ���������
	float Amainhsangle;
	int Atower;
	int Agun;
	int Ahousing;
	GameObj animhs;
	GameObj animt;
	GameObj animg;
	GameObj animbhbphspbhbp;
	GameObj mainbhbphspbhbp;
	float ratio;
	float mainhp;
	Timer AshellTimer;
	float artm;
	bool Adestroed;
	///////////////////////������
	int Agusliy;
	int Adviglo;
	int Abashnia;
	int Atriplex;
	int Adulo;
	int Abk;
	int Aradio;
	///////////////////////������
	int Acom;
	int Azar;
	int Araddist;
	int Amesh_vod;
	int Anavod;
	///////////////////////////////
	FromDesign(GameView, gamepole);
	LayerFromDesign(void, bhbp);
	FromDesign(Button, newgame);
	FromDesign(Button, loadgame);
	FromDesign(Button, howtoplay);
	FromDesign(Button, exit);
	FromDesign(FilledRect, blk);
	FromDesign(Layout, stolb1);
	LayerFromDesign(void, graund);
    LayerFromDesign(void, clay);
	FromDesign(Layout, kpk);
	

	vector<gundata> gddos;
	vector<tdata> tddos;
	vector<hsdata> hsddos;
};

int main(int argc, char** argv)
{
	MyApp app;
	app.setConfig("ProjectTankiXConfig.json");
	app.setDesign("Design.json");
	if (!app.init(&argc, argv))
		return 1;
	app.run();
	return 0;
}
