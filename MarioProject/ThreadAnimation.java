

public class ThreadAnimation extends Thread{
	private Handler H;
	
	public ThreadAnimation(Handler H){
		this.H = H;
	}
	
	public void run(){
		while(true){
			this.animation_update();
			try{
				Thread.sleep(C.timval);
			}catch(InterruptedException ex){}
		}
	}
	public void animation_update(){
		//H.player.animation_update();
		
		this.animation(H.player);
		this.animation(H.enemies);
	}
	public void animation(ImgSprite comp){
		comp.animation_update();
	}
	public void animation(ImgSprite[] list){
		for (int i = 0; i < list.length; i++){
			list[i].animation_update();
		}
	}
}
