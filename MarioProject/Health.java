

public class Health extends UnsignedCounter{
	public static final int MaxHealth = 40;
	public static final int MotionlessPenaltyInterval = 10;
	public static final int MotionlessPenalty = 5;
	public static final int MovingBonus = 1;
	public static final int KillEnemyBonus = 10;
	public static final int GotHitPenalty = 5;
	
	public Health(int value){
		super(value);
	}
	public void increment(){
		super.increment();
		if (this.value() > Health.MaxHealth){
			this.setVal(Health.MaxHealth);
		}
	}
	public void increase(int x){
		super.increase(x);
		if (this.value() > Health.MaxHealth){
			this.setVal(Health.MaxHealth);
		}
	}
	
}
