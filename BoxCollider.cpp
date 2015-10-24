#include "BoxCollider.h"


BoxCollider::BoxCollider(void)
{
}


BoxCollider::~BoxCollider(void)
{
}

void BoxCollider::Init()
{
	Collider::Init();
}

void BoxCollider::Update()
{
	Collider::Update();
}

void BoxCollider::BoxBoxCollision(BoxCollider &a, BoxCollider &b)
 {
	vec2 overlapAmnt;
	vec2 responseDirA;
	vec2 responseDirB;

	Rect ra = a.tf->rectangle;
	Rect rb = b.tf->rectangle;
	
	// check if both are stationary, do nothing
	if(a.stationary)
		return;

	// basic overlap check
	if(ra.left > rb.right || ra.right < rb.left ||
		ra.top > rb.bottom || ra.bottom < rb.top)
		return;
 
	// calc amount that the rects overlap
	if(ra.center.x < rb.center.x)
		overlapAmnt.x = ra.right - rb.left;
	else
		overlapAmnt.x = rb.right - ra.left;
	if(ra.center.y < rb.center.y)
		overlapAmnt.y = rb.top - ra.bottom;
	else
		overlapAmnt.y = ra.top - rb.bottom;
		
	// determine cardinal vector for response based upon collider movement
	float xAmntA = DotProd(a.tf->deltaPosition, vec2(1,0));
	float yAmntA = DotProd(a.tf->deltaPosition, vec2(0,1));
	
	float moveDiff = abs(xAmntA) - abs(yAmntA);
	
	//if(abs(xAmntA) > abs(yAmntA)) // move horizontally
	//	responseDirA.x = xAmntA > 0 ? -1.f : 1.f;
	//else if(abs(yAmntA) > abs(xAmntA)) // move vertically
	//	responseDirA.y = yAmntA > 0 ? -1.f : 1.f;

	if(abs(overlapAmnt.x) < abs(overlapAmnt.y))
	{
		responseDirA.x = ra.center.x < rb.center.x ? -1 : 1;
	}
	else
	{
		responseDirA.y = ra.center.y < rb.center.y ? -1 : 1;
	}

	if(a.stationary)
		responseDirA = vec2::zero();
		
	// both non-stationary, move them both apart
	float multiplier = 1.f;
	if(!a.stationary && !b.stationary)
		multiplier - 0.5f;
	
	if(!a.stationary)
	{
		vec2 totalResponseA = vec2(
			responseDirA.x * abs(overlapAmnt.x) * multiplier,
			responseDirA.y * abs(overlapAmnt.y) * multiplier);
		a.tf->MovePos(totalResponseA);
	}

 }

 