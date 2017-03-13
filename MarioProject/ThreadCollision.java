

import java.util.Iterator;

public class ThreadCollision extends Thread{
	private Handler H;
	
	public ThreadCollision(Handler H){
		this.H = H;
	}
	
	public void run(){
		while(true){
			this.collision_update();
			/*
			try{
				Thread.sleep(C.timval);
			}catch(InterruptedException ex){}
			*/
		}
	}
	
	public void collision_update(){
		if (H.player.is_fainted()){
			return;
		}
		collision(H.player, H.enemies);
		
	}
	
	// player <-> enemies       => player fainted, game over
	// player <-> enemies blist => player health decreases, bullet inactive
	// player blist <-> enemies => Enemy fainted, score increase
	// player blist <-> enemies blist => both bullets inactive
	public void collision(Player player, Enemy[] enemies){
		for (int i = 0; i < enemies.length; i++){
			if (!enemies[i].is_fainted() && player.collideWith(enemies[i])){
				player.get_killed();
				//System.out.println("player fainted");
			}
			synchronized(enemies[i].blist){
				Iterator<Bullet> iter = enemies[i].blist.iterator();
				while (iter.hasNext()){
					Bullet tmp = iter.next();
					if (tmp.is_active() && player.collideWith(tmp)){
						tmp.inactive();
						H.health.decrease(Health.GotHitPenalty);
						H.sound.play(SoundEffect.PlayerGotHit);
						//System.out.println("player health decreases");
					}
				}
			}
		}
		synchronized(player.blist){
			Iterator<Bullet> iter = player.blist.iterator();
			while(iter.hasNext()){
				Bullet pb = iter.next();
				if (pb.is_active()){
					for (int j = 0; j < enemies.length; j++){
						if (!enemies[j].is_fainted() && pb.collideWith(enemies[j])){
							enemies[j].get_killed();
							pb.inactive();
							H.health.increase(Health.KillEnemyBonus);
							H.score.increment();
							H.sound.play(SoundEffect.EnemyGotHit);
							//System.out.println("Score increases");
						}else{
							synchronized(enemies[j].blist){
								Iterator<Bullet> iter2 = enemies[j].blist.iterator();
								while(iter2.hasNext()){
									Bullet eb = iter2.next();
									if (eb.is_active() && eb.collideWith(pb)){
										eb.inactive();
										pb.inactive();
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	
	
	
}
