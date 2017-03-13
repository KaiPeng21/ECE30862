

public class ThreadShooting extends Thread{
	private Handler H;
	
	public ThreadShooting(Handler H){
		this.H = H;
	}
	
	public void run(){
		while(true){
			this.shooting_update();
			try{
				Thread.sleep(C.timval);
			}catch(InterruptedException ex){}
		}
	}
	
	public void shooting_update(){
		if (H.player.is_fainted()){
			return;
		}
		
		this.shooting(H.player);
		this.shooting(H.enemies);
		//H.player.shooting_update();
	}
	public void shooting(Shooting comp){
		comp.shooting_update();
	}
	public void shooting(Shooting[] list){
		for (int i = 0; i < list.length; i++){
			list[i].shooting_update();
		}
	}
}
