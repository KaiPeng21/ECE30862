
import java.awt.Image;

public abstract class MoveComponent extends Component{
	protected double velX;
	protected double velY;
	protected double accX;
	protected double accY;
	
	public MoveComponent(Image img){
		super(img);
	}
	public MoveComponent(Image img, double x, double y){
		super(img,x,y);
	}
	
	public void setVel(double velX, double velY){
		this.velX = velX;
		this.velY = velY;
	}
	public void setVelX(double velX){
		this.velX = velX;
	}
	public void setVelY(double velY){
		this.velY = velY;
	}
	public void setAcc(double accX, double accY){
		this.accX = accX;
		this.accY = accY;
	}
	public void setAccX(double accX){
		this.accX = accX;
	}
	public void setAccY(double accY){
		this.accY = accY;
	}
	public double velX(){
		return this.velX;
	}
	public double velY(){
		return this.velY;
	}
	public double accX(){
		return this.accX;
	}
	public double accY(){
		return this.accY;
	}
	public void stop_horizontal_movement(){
		this.accX = 0;
		this.velX = 0;
	}
	public void stop_vertical_movement(){
		this.accY = 0;
		this.velY = 0;
	}
	public void stop_movement(){
		this.stop_horizontal_movement();
		this.stop_vertical_movement();
	}
	
	public void movement_update(){
		this.velX += this.accX;
		this.velY += this.accY;
		
		if (this.velX > C.velXLimit){
			this.velX = C.velXLimit;
		}else if (this.velX < -C.velXLimit){
			this.velX = -C.velXLimit;
		}
		
		if (this.velY > C.velYLimit){
			this.velY = C.velYLimit;
		}else if (this.velY < -C.velYLimit){
			this.velY = -C.velYLimit;
		}
		
		this.x += this.velX;
		this.y += this.velY;
	}
}
