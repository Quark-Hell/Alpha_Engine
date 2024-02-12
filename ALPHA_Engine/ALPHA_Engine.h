

class GameFunction {
public:
	virtual void Start();
	virtual void Update();

};

void InitSun();

void InitPlanet1();
void InitPlanet2();

void SetControl();

void LeftMoveTestObject();
void RightMoveTestObject();

void ForwardMoveTestObject();
void BackwardMoveTestObject();

void UpMoveTestObject();
void DownMoveTestObject();

void LeftMoveCamera();
void RightMoveCamera();

void ForwardMoveCamera();
void BackwardMoveCamera();

void UpMoveCamera();
void DownMoveCamera();

void Stop();
void Jump();

void CameraRotate();

