

import java.awt.Image;
import java.util.List;
import java.util.Iterator;

public abstract class Component {
	public Image img;
	protected int w = 0;
	protected int h = 0;
	protected double x = 0;
	protected double y = 0;
	protected int facing = C.Right;
	
	public Component(Image img){
		this.img = img;
		this.w = img.getWidth(null);
		this.h = img.getHeight(null);
		this.x = Dim.WIDTH/2;
		this.y = Dim.HEIGHT/2;
	}
	public Component(Image img, double x, double y){
		this.img = img;
		this.w = img.getWidth(null);
		this.h = img.getHeight(null);
		this.x = x;
		this.y = y;
	}
	public void setImg(Image img){
		this.img = img;
	}
	public int facing(){
		return this.facing;
	}
	public void set_facing(int dir){
		this.facing = dir;
	}
	public double x(){
		return x;
	}
	public double y(){
		return y;
	}
	public int x_int(){
		return (int) x;
	}
	public int y_int(){
		return (int) y;
	}
	public void setPos(double x, double y){
		this.x = x;
		this.y = y;
	}
	public int h(){
		return h;
	}
	public int w(){
		return w;
	}
	public int left(){
		return (int)this.x;
	}
	public int right(){
		return (int)this.x + this.w;
	}
	public int top(){
		return (int)this.y;
	}
	public int bottom(){
		return (int)this.y + this.h;
	}
	public int cx(){
		return (this.left() + this.right()) / 2;
	}
	public int cy(){
		return (this.top() + this.bottom()) / 2;
	}
	public boolean is_in_the_screen(){
		return this.is_in_the_screen_horizontal() && this.is_in_the_screen_vertical();
	}
	public boolean is_in_the_screen_horizontal(){
		return this.left() >= 0 && this.right() <= Dim.WIDTH;
	}
	public boolean is_in_the_screen_vertical(){
		return this.top() >= 0 && this.bottom() <= Dim.HEIGHT;
	}
	
	public boolean collideWith(Component o1){
		return collideXWith(o1) && collideYWith(o1);
	}
	public boolean collideXWith(Component o1){
		if (o1 == null){
			return false;
		}
		if (this.x() < o1.x()+o1.w() && o1.x() < this.x()+this.w()){
			return true;
		}
		return false;
	}
	public boolean collideYWith(Component o1){
		if (o1 == null){
			return false;
		}
		if (this.y() < o1.y()+o1.h() && o1.y() < this.y()+this.h()){
			return true;
		}
		return false;
	}
	public boolean collideWith(Component[] list){
		for (int i = 0; i < list.length; i++){
			if (this.collideWith(list[i])){
				return true;
			}
		}
		return false;
	}
	public boolean collideWith(List<Bullet> list){
		synchronized(list){
			Iterator<Bullet> iter = list.iterator();
			while (iter.hasNext()){
				Bullet tmp = iter.next();
				if (tmp.active){
					if (this.collideWith(tmp)){
						return true;
					}
				}
			}
		}		
		return false;
	}
}
