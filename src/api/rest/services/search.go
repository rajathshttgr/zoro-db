package services

import (
	"errors"
	"zoro/api/core"
)

func GetPointById(collectionName string, pointId int) (*core.PointRetrival, error) {

	if pointId <= 0 {
		return nil, errors.New("point id seems invalid")
	}

	return core.GetPointById(collectionName, pointId)
}
