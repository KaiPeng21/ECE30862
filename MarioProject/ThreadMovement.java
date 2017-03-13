

import java.util.List;
import java.util.Iterator;

public class ThreadMovement extends Thread{
	private Handler H;
	
	public ThreadMovement(Handler H){
		this.H = H;
	}
	public void run(){
		while(true){
			this.movement_update();
			
			try{
				Thread.sleep(C.timval);
			}catch(InterruptedException ex){}
			
		}
	}
	public void movement_update(){
		if (H.player.is_fainted()){
			return;
		}
		/*
		H.player.movement_update();
		synchronized(H.player.blist){
			Iterator<Bullet> iter = H.player.blist.iterator();
			while (iter.hasNext()){
				iter.next().movement_update();
			}
		}		
		for (int i = 0; i < H.enemies.length; i++){
			H.enemies[i].movement_update();
		}
		*/
		this.movement(H.player);
		this.movement(H.player.blist);
		this.movement(H.enemies);
		for (int i = 0; i < H.enemies.length; i++){
			this.movement(H.enemies[i].blist);
		}
		
		this.relative_motion();
	}
	public void movement(MoveComponent comp){
		comp.movement_update();
	}
	public void movement(MoveComponent[] list){
		for (int i = 0; i < list.length; i++){
			list[i].movement_update();
		}
	}
	public void movement(List<Bullet> list){
		synchronized(list){
			Iterator<Bullet> iter = list.iterator();
			while(iter.hasNext()){
				Bullet tmp = iter.next();
				if (tmp.is_active()){
					tmp.movement_update();
				}
			}
		}
	}
	
	
	public void relative_motion(){
		if (H.player.is_fainted()){
			return;
		}
		
		double pvX = H.player.velX();
		double pvY = H.player.velY();
		
		this.relative(H.player, pvX, pvY);
		this.relative(H.player.blist, pvX, pvY);
		this.relative(H.blk_normal, pvX, pvY);
		this.relative(H.enemies, pvX, pvY);
		for (int i = 0; i < H.enemies.length; i++){
			this.relative(H.enemies[i].blist, pvX, pvY);
		}
		
	}
	public void relative(MoveComponent comp, double pvX, double pvY){
		comp.setPos(comp.x()-pvX, comp.y()-pvY);
	}
	public void relative(MoveComponent[] list, double pvX, double pvY){
		for (int i = 0; i < list.length; i++){
			this.relative(list[i], pvX, pvY);
		}
	}
	public void relative(List<Bullet> list, double pvX, double pvY){
		synchronized(list){
			Iterator<Bullet> iter = list.iterator();
			while (iter.hasNext()){
				Bullet tmp = iter.next();
				if (tmp.is_active()){
					this.relative(tmp, pvX, pvY);			
				}
			}
		}

	}
	
}
