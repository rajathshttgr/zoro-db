package services

import (
	"errors"
	"zoro/core"
	"zoro/dto"
)

func UpsertPoints(
	collectionName string,
	points []dto.PointData,
) (int, error) {

	if collectionName == "" {
		return -1, errors.New("collection name must not be empty")
	}

	if len(points)==0{
		return -1, errors.New("Minimum one point is required")
	}

	operationId, err := core.UpsertPoints(
		collectionName,
		points,
	)

	if err != nil {
		return -1, err
	}

	return operationId, nil
}

func DeletePoints(collectionName string, ids []int) error {
	if len(ids) == 0 {
		return errors.New("ids must not be empty")
	}

	return core.DeletePoints(collectionName, ids)
}

func GetPointCount(collection_name string) (int, error) {
	count, err := core.CountPoints(collection_name)
	if err != nil {
		return 0, err
	}

	return count, nil
}