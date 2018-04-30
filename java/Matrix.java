/*
 * Matrix.java
 * A Simple class to represent matrix data structure
 * Implemented by Thomas Sunghoon Heo
 * Compile : javac Matrix.java
 */
 
 class Matrix{
 	private static int ROWS;
	private static int COLS;
	private static double element[];
 	public Matrix(int rows, int cols){
		ROWS= rows;
		COLS = cols;
		element = new double[rows * cols];
	}
	public double GetElemAt(int r, int c){
		return element[r * COLS + c];
	}
	public double SetElemAt(int r, int c, double v){
		element[r * COLS + c] = v;
	}
	public int GetNumRows(){
		return ROWS;
	}
	public int GetNumCols(){
		return COLS;
	}
	public double[] GetMatrix(){
		return element;
	}
	public Matrix multiply(Matrix other){
		int otherCols = other.GetNumCols();
		int otherRows = other.GetNumRows();
		Matrix M = new Matrix(ROWS, otherCols);
		for(int i = 0; i < ROWS; i++){
			for(int j = 0; j < otherCols; j++){
				double s = 0.0;
				for (int k = 0; k < otherRows; k++){
					double aik = this.GetElemAt(i,k);
					double bkj = other.GetElemAt(k,j);
					s += aik * bkj;
				}
				M.SetElemAt(i,j,s);
			}
		}
		return M;
	}
	public Matrix Transpose(){
		// transpose itself
		Matrix M = new Matrix(COLS, ROWS);
		for(int i = 0; i < ROWS; i++){
			for(int j = 0; j < COLS; j++){
				double v = this.GetElemAt(i,j);
				M.SetElemAt(j,i,v);
			}
		}
		return M;
	}
	public double Trace(){
		int lim = ROWS < COLS ? ROWs : COLS;
		double thing = 0.0;
		for(int i = 0; i < lim; i++){
			thing += this.GetElemAt(i,i);
		}
		return thing;
	}
 } // end of class Matrix
