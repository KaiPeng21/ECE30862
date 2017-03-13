

import java.awt.event.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public class Player extends MoveComponent implements ImgSprite, KeyInterrupted, Shooting{
    private Handler H;
	private boolean is_fainted;
	
	/*Image Sprite Animation*/
	public int animating_status;
	private int ani_ct;
	public static final int standing = 0;
	public static final int moving = 1;
	public static final int gothit = 2;
	
	/*Shooting Mechanism*/
	public List<Bullet> blist = Collections.synchronizedList(new ArrayList<Bullet>());
	private boolean keyUp, cooldown;
	private int kpct, shct, clct;
	
	
	public Player(Handler H){
		super(ImgPool.player_stand[0],2*Dim.UNIT_W,Dim.HEIGHT-Dim.UNIT_H-100);
		this.H = H;
		this.is_fainted = false;
		
		this.animating_status = Player.standing;
		this.ani_ct = 0;
		
		this.keyUp = true;
		this.cooldown = false;
		this.kpct = this.shct = this.clct = 0;
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
		if (this.is_fainted){
			if (this.ani_ct >= ImgPool.player_gothit.length){
				this.ani_ct = 0;
			}
			this.setImg(ImgPool.player_gothit[this.ani_ct]);
		}else{
			if (this.animating_status == Player.standing){
				if (this.ani_ct >= ImgPool.player_stand.length){
					this.ani_ct = 0;
				}
				this.setImg(ImgPool.player_stand[this.ani_ct]);
			}else if (this.animating_status == Player.moving){
				if (this.ani_ct >= ImgPool.player_move.length){
					this.ani_ct = 0;
				}
				this.setImg(ImgPool.player_move[this.ani_ct]);
			}else if (this.animating_status == Player.gothit){
				if (this.ani_ct >= ImgPool.player_gothit.length){
					this.ani_ct = 0;
				}
				this.setImg(ImgPool.player_gothit[this.ani_ct]);
			}
		}
		
		this.ani_ct++;
	}
	
	public void movement_update(){
		if (this.is_fainted){
			return;
		}
		
		super.movement_update();
		if (this.velX > 0){
			this.animating_status = Player.moving;
			this.facing = C.Right;
		}else if (this.velX < 0){
			this.animating_status = Player.moving;
			this.facing = C.Left;
		}else{
			this.animating_status = Player.standing;
		}
		
		
		//System.out.println(this.x + " " + this.y + " " + this.velX);
	}
	public void move_left(){
		this.setAccX(-3);
	}
	public void move_right(){
		this.setAccX(3);
	}
	
	public void shooting_update(){
		if (this.is_fainted){
			return;
		}
		
		if (!this.keyUp){
			this.kpct++;
		}else{
			this.kpct = 0;
		}
		
		if (this.kpct == 1 && !this.cooldown){        // shoot when pressed once
			this.shoot();
		}else if (this.kpct >= 15 && !this.cooldown){  // continuous
			this.shoot();
			this.shct++;
		}
		
		if (this.shct > C.ShootingLimit){ // 10
			this.shct = 0;
			this.cooldown = true;
		}
		
		if (this.cooldown){
			this.clct++;
			if (this.clct > C.CooldownInterval){ // 10
				this.cooldown = false;
			}
		}else{
			this.clct = 0;
		}
		
		//System.out.println(" keyUp " + this.keyUp + " kpct " + this.kpct + " shct " + this.shct + " cooldown " + this.cooldown + " clct " + this.clct);
	}
	
	public void shoot(){
		this.blist.add(new Bullet(ImgPool.bullet_player, this.cx(), this.cy(), this.facing()));
		H.sound.play(SoundEffect.PlayerShoot);
	}
	
	public void keyPressed(KeyEvent e){
		int keycode = e.getKeyCode();
		switch(keycode){
		case KeyEvent.VK_LEFT:
			this.move_left(); 
			break;
		case KeyEvent.VK_RIGHT:
			this.move_right(); 
			break;
		case KeyEvent.VK_UP:
			//this.jump_start(); 
			break;
		case KeyEvent.VK_DOWN:
			//this.jump_down(); 
			break;
		case KeyEvent.VK_S:
			this.keyUp = false;
			break;
		}
	}
	public void keyReleased(KeyEvent e){
		int keycode = e.getKeyCode();
		switch(keycode){
		case KeyEvent.VK_LEFT:
			this.stop_horizontal_movement(); 
			break;
		case KeyEvent.VK_RIGHT:
			this.stop_horizontal_movement(); 
			break;
		case KeyEvent.VK_UP:
			//this.jump_start(); 
			break;
		case KeyEvent.VK_DOWN:
			//this.jump_down(); 
			break;
		case KeyEvent.VK_S: 
			this.keyUp = true;
			break;
		}
	}
}
