

public class ThreadHealthCheck extends Thread{
	private Handler H;
	private int motionless_ct;
	private double Xtraveld;
	
	public ThreadHealthCheck(Handler H){
		this.H = H;
		this.motionless_ct = 0;
		this.Xtraveld = 0;
	}
	
	public void run(){
		while(true){
			this.healthcheck_update();
			try{
				Thread.sleep(C.timval);
			}catch(InterruptedException ex){}
		}
	}
	public void healthcheck_update(){
		if (H.player.velX == 0 && H.player.velY == 0){
			this.motionless_ct++;
			if (this.motionless_ct > Health.MotionlessPenaltyInterval){
				H.health.decrease(Health.MotionlessPenalty);
				this.motionless_ct = 0;
			}
		}else{
			this.motionless_ct = 0;
		}
		
		this.Xtraveld += Math.abs(H.player.velX);
		if (this.Xtraveld >= Dim.UNIT_W){
			H.health.increase(Health.MovingBonus);
			this.Xtraveld = 0;
		}
		
		if (H.player.is_fainted()){
			H.health.zero();
		}
		if (H.health.value() == 0){
			H.player.get_killed();
		}
	}
}
