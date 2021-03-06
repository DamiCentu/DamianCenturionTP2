// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerProjectile.h"
#include "PaperCharacterParcial.h"


// Sets default values
APlayerProjectile::APlayerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerProjectile::SetImpulse(FVector direction) {

	_boxCollider = FindComponentByClass < UBoxComponent>();

	if (_boxCollider) {
		_boxCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerProjectile::OnBoxBeginOverlap);
	}

	if (_boxCollider)
	{
		_boxCollider->AddImpulse(direction * force);
	}
}

void APlayerProjectile::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA<APaperCharacterParcial>() || OtherActor->IsA<ATriggerVolume>())
		return;

	IOnHit * hitActor = Cast<IOnHit>(OtherActor);
	if (hitActor) {
		hitActor->OnHit();
	}
	Destroy();
}

