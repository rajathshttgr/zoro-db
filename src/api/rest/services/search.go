package services

import (
	"errors"
	"zoro/api/core"
)

func SearchPoints(
    collectionName string,
    vectors []float32,
    limit int,
) (*core.SearchPointRetrival, error) {

    if limit <= 0 {
        return nil, errors.New("limit should be greater than 0")
    }

	if len(vectors) == 0 {
		return nil, errors.New("vectors must not be empty")
	}

	collectionInfo, err := core.GetCollectionInfo(collectionName)
	if err != nil {
		return nil, err
	}

	if len(vectors) != collectionInfo.Dimension {
		return nil, errors.New("vector dimension does not match collection dimension")
	}

    points, err := core.SearchPointsByVector(collectionName, vectors, limit)
    if err != nil {
        return nil, err
    }

    return &core.SearchPointRetrival{
        Points: points,
        Count:  len(points),
    }, nil
}

func GetPointById(collectionName string, pointId int) (*core.PointRetrival, error) {

	if pointId <= 0 {
		return nil, errors.New("point id seems invalid")
	}

	return core.GetPointById(collectionName, pointId)
}


func ScrollPoints(
    collectionName string,
    limit int,
) (*core.ScrollPointsRetrival, error) {

    if limit <= 0 {
        return nil, errors.New("limit should be greater than 0")
    }

    points, err := core.ScrollPointsDataRetrival(collectionName, limit)
    if err != nil {
        return nil, err
    }

    return &core.ScrollPointsRetrival{
        Points: points,
        Count:  len(points),
    }, nil
}
