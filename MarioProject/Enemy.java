

import java.util.Collections;
import java.util.List;
import java.util.ArrayList;

public class Enemy extends MoveComponent implements ImgSprite, Shooting{
	private Handler H;
	private boolean is_fainted;
	
	/*Animation*/
	private int ani_ct;
	
	/*Shooting Mechanism*/
	public List<Bullet> blist = Collections.synchronizedList(new ArrayList<Bullet>());
	private int fct, wct;
	private boolean awake;
	
	public Enemy(Handler H, double x, double y){
		super(ImgPool.enemy_stand[0],x,y);
		this.H = H;
		this.is_fainted = false;
		this.ani_ct = 0;
		this.fct = this.wct = 0;
		this.awake = false;
	}
	public boolean is_fainted(){
		return this.is_fainted;
	}
	public void set_is_fainted(boolean is_fainted){
		this.is_fainted = is_fainted;
	}
	public void get_killed(){
		this.is_fainted = true;
	}
	
	public void animation_update(){
		if (!is_fainted){
			if (this.ani_ct >= ImgPool.enemy_stand.length){
				this.ani_ct = 0;
			}
			this.setImg(ImgPool.enemy_stand[this.ani_ct]);
		}else{
			if (this.ani_ct >= ImgPool.enemy_gothit.length){
				this.ani_ct = 0;
			}
			this.setImg(ImgPool.enemy_gothit[this.ani_ct]);
		}
		
		this.ani_ct++;
	}
	public void movement_update(){
		if (this.is_fainted){
			return;
		}
		
		super.movement_update();
		
		if (this.is_in_the_screen()){
			this.wct++;
			if (this.wct > C.EnemyWaitInterval){
				this.awake = true;
			}
		}else{
			this.awake = false;
			this.wct = 0;
		}
		
		if (this.awake){
			if (this.right() < H.player.left()){
				this.set_facing(C.Right);
				this.setVelX(1);
			}else if (this.left() > H.player.right()){
				this.set_facing(C.Left);
				this.setVelX(-1);
			}else{
				this.stop_horizontal_movement();
			}
		}else{
			this.stop_horizontal_movement();
		}
	}
	public void shooting_update(){
		if (this.is_fainted){
			return;
		}
		
		if (this.awake){
			this.fct++;
			if (this.fct % 2 == 0){
				this.shoot();
			}
		}
	}
	public void shoot(){
		this.blist.add(new Bullet(ImgPool.bullet_enemy, this.cx(), this.cy(), this.facing()));
		H.sound.play(SoundEffect.EnemyShoot);
	}
	
}
