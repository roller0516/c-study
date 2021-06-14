using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Monster : MonoBehaviour
{
    public Renderer render;

    int hp;
    int maxHp;
    Animator ani;
    NavMeshAgent agent;
    Player player;
    new Collider collider;
    void Start()
    {
        maxHp = 100;
        hp = maxHp;
        ani = this.gameObject.GetComponent<Animator>();
        player = GameObject.FindWithTag("Player").GetComponent<Player>();
        collider = this.gameObject.GetComponent<Collider>();
       
        //material = this.gameObject.GetComponent<Material>();
    }

    // Update is called once per frame
    void Update()
    {
        if (hp < 0) 
        {
            ani.SetBool("IsDie", true);
            collider.enabled = false;
            render.material.color = new Color(render.material.color.r, render.material.color.g, render.material.color.b, 150);
        }
    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Sword") 
        {
            hp -= player.playerAttack;
            ani.SetBool("IsHit", true);
            
        }
    }
    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "Sword")
        {
            ani.SetBool("IsHit", false);
        }
    }

}
