package services

import (
	"errors"
	"zoro/api/core"
)

	
func UpsertPoints(
	collectionName string,
	vectors [][]float32,
	ids []int,
	payload []map[string]any,
) error {

	if len(vectors) == 0 {
		return nil
	}

	if len(vectors) != len(ids) {
		return errors.New("vectors and ids must have the same length")
	}

	if payload != nil && len(payload) != len(vectors) {
		return errors.New("payload must be nil or have the same length as vectors")
	}

	// Normalize payload
	if payload == nil {
		payload = make([]map[string]any, len(vectors))
	}

	// Validate vector dimensions
	dim := len(vectors[0])
	for _, vec := range vectors {
		if len(vec) != dim {
			return errors.New("all vectors must have the same dimension")
		}
	}

	// Validate collection dimension
	collectionInfo, err := core.GetCollectionInfo(collectionName)
	if err != nil {
		return err
	}

	if collectionInfo.Dimension != dim {
		return errors.New("vector dimension does not match collection dimension")
	}

	return core.UpsertPoints(
		collectionName,
		vectors,
		ids,
		payload,
	)
}

func DeletePoints(collectionName string, ids []int) error {
	if len(ids) == 0 {
		return nil
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

func GetPointById(collectionName string, pointId int) (*core.PointRetrival, error) {

	if pointId <= 0 {
		return nil, errors.New("point id seems invalid")
	}

	return core.GetPointById(collectionName, pointId)
}