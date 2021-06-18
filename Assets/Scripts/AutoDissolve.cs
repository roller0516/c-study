using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AutoDissolve : MonoBehaviour
{
    public bool isDissolve = false;
    MeshRenderer[] meshRenderers;

    private void OnEnable()
    {
        isDissolve = false;
        if (meshRenderers == null) return;

        foreach (var meshRenderer in meshRenderers)
        {
            var color = meshRenderer.material.color;
            color.a = 1f;
            meshRenderer.material.color = color;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        meshRenderers = GetComponentsInChildren<MeshRenderer>();    
    }

    // Update is called once per frame
    void Update()
    {

        if (gameObject.transform.position.x < -1) 
            ObjectPool.instance.ReturnToPool("PlatForm", gameObject);

        if (!isDissolve) return;

        foreach(var meshRenderer in meshRenderers)
        {
            var color = meshRenderer.material.color;
            color.a -= (Time.deltaTime / 5.0f);
            if (color.a <= 0f)
            {
                color.a = 0f;
            }
            meshRenderer.material.color = color;
        }
        
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Player" && !isDissolve)
        {
            isDissolve = true;
        }
    }
}
