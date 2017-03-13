

public class UnsignedCounter {
	private int value;
	private int resetVal;
	
	public UnsignedCounter(){
		this.resetVal = 0;
		this.value = 0;
	}
	public UnsignedCounter(int value){
		this.resetVal = value;
		this.value = value;
	}
	
	public String toString(){
		return "" + this.value;
	}
	public int value(){
		return this.value;
	}
	public void setVal(int value){
		this.value = value;
	}
	public void increment(){
		this.value++;
	}
	public void decrement(){
		this.value--;
		if (this.value < 0){
			this.value = 0;
		}
	}
	public void increase(int x){
		this.value += x;
	}
	public void decrease(int x){
		this.value -= x;
		if (this.value < 0){
			this.value = 0;
		}
	}
	public void reset(){
		this.value = this.resetVal;
	}
	public void zero(){
		this.value = 0;
	}
}
