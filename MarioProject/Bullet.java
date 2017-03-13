
import java.awt.Image;

public class Bullet extends MoveComponent{
	public boolean active;
	private double deltaX;
	
	public Bullet(Image img, double x, double y, int dir){
		super(img, x, y);
		this.deltaX = 0;
		this.active = true;
		this.facing = dir;
	}
	
	public void movement_update(){
		if (this.active){
			if (this.facing() == C.Right){
				this.setVelX(C.BulletSpeed);
			}else{
				this.setVelX(-C.BulletSpeed);
			}
			this.setPos(this.x()+this.velX, this.y());
			if (!this.is_in_the_screen()){
				this.inactive();
			}
		}
		
		this.deltaX += Math.abs(this.velX);
		if (this.deltaX > C.BulletDuration){
			this.inactive();
		}
		//System.out.println(this.velX);
	}
	public boolean is_active(){
		return this.active;
	}
	public void inactive(){
		this.active = false;
	}

}
