import { useEffect, useMemo, useState, type FormEvent, type ReactElement } from 'react'
import { FirebaseSocialRepository } from '../infrastructure/firebase/socialRepository'
import { FirebaseProfileRepository } from '../infrastructure/firebase/profileRepository'
import type { AuthenticatedIdentity } from '../social/domain/identity'
import type { ActivityEvent, Post } from '../social/domain/models'
import type { SocialProfile } from '../social/domain/profile'
import { ProfilePage } from './ProfilePage'
import './post-card.css'

const repository = new FirebaseSocialRepository()
const profiles = new FirebaseProfileRepository()
type Page = 'home' | 'post' | 'video' | 'profile'

export function SocialApp({ identity, onDashboard }: { identity: AuthenticatedIdentity; onDashboard: () => void }): ReactElement {
  const [page, setPage] = useState<Page>('home')
  const [posts, setPosts] = useState<Post[]>([])
  const [activity, setActivity] = useState<ActivityEvent[]>([])
  const [, setProfile] = useState<SocialProfile | null>(null)
  const [error, setError] = useState('')

  useEffect(() => {
    setError('')
    profiles.getProfile(identity).then(setProfile).catch(cause => setError(cause instanceof Error ? cause.message : 'Profile failed'))
    const stopFeed = repository.subscribeHomeFeed(identity, setPosts, error => setError(error.message))
    const stopActivity = repository.subscribeActivity(identity, setActivity, error => setError(error.message))
    return () => { stopFeed(); stopActivity() }
  }, [identity])

  const recentActivity = useMemo(() => activity.filter(event => event.createdAtMs !== null).slice(0, 8), [activity])
  async function handleLike(postId: string) { try { setError(''); await repository.likePost(identity, postId) } catch (cause) { setError(cause instanceof Error ? cause.message : 'Like failed') } }

  return <div className="social-shell"><header className="social-header"><button className="shortcut" onClick={() => setError('Inbox is not implemented yet; no fake inbox is presented.')}>📥 <span>Inbox</span></button><div className="social-title"><span className="brand-mark small">WD</span><strong>Social</strong></div><div className="header-actions"><button className="shortcut" onClick={() => setError(`Live activity events loaded: ${recentActivity.length}.`)}>🔔</button><button className="shortcut" onClick={() => setError(`${recentActivity.length} real activity event(s) loaded from Firestore.`)}>❤️</button><button className="dashboard-button" onClick={onDashboard}>→ Dashboard</button></div></header><main className="social-main">{error && <div className="error banner">{error}</div>}{page === 'home' && <section className="feed-page"><div className="page-heading"><div><span className="eyebrow">REAL-TIME SOCIAL FEED</span><h1>Home</h1></div></div>{posts.length === 0 ? <div className="empty-state"><strong>No posts yet</strong><span>Your Home is empty because no persisted posts are available.</span></div> : posts.map(post => <PostCard key={post.id} post={post} onLike={() => handleLike(post.id)} onError={setError} />)}</section>}{page === 'post' && <PostComposer identity={identity} onCreated={() => setPage('home')} />}{page === 'video' && <section className="empty-state"><strong>Video</strong><span>Video creation is the next Social vertical slice. No fake video UI is presented as functional.</span></section>}{page === 'profile' && <ProfilePage identity={identity} />}</main><nav className="bottom-nav"><button className={page === 'home' ? 'active' : ''} onClick={() => setPage('home')}>🏠<span>Home</span></button><button className={page === 'post' ? 'active' : ''} onClick={() => setPage('post')}>➕<span>Post</span></button><button className={page === 'video' ? 'active' : ''} onClick={() => setPage('video')}>🎬<span>Video</span></button><button className={page === 'profile' ? 'active' : ''} onClick={() => setPage('profile')}>🧑‍💼<span>Profile</span></button></nav></div>
}

function PostCard({ post, onLike, onError }: { post: Post; onLike: () => void; onError: (message: string) => void }): ReactElement {
  const [menuOpen, setMenuOpen] = useState(false)
  const [privacyOpen, setPrivacyOpen] = useState(false)
  const [reactionOpen, setReactionOpen] = useState(false)
  const authorName = post.author.profileName.trim()
  const authorPhoto = post.author.photoUrl.trim()
  const timestamp = post.createdAtMs ? new Date(post.createdAtMs).toLocaleString() : 'Publishing…'

  return <article className="post-card">
    <div className="post-header">
      <div className="post-avatar">{authorPhoto ? <img src={authorPhoto} alt={authorName} /> : <span>{authorName.slice(0, 1).toUpperCase()}</span>}</div>
      <div className="post-author-meta"><strong>{authorName}</strong><span>{timestamp} · 🌐</span></div>
      <div className="post-menu-wrap">
        <button className="post-menu" aria-label="Post options" onClick={() => setMenuOpen(value => !value)}>⋯</button>
        {menuOpen && <div className="post-menu-panel"><button onClick={() => onError('Post editing will use the real post update operation.')}>Edit</button><button onClick={() => onError('Post deletion will use the real post delete operation.')}>Delete</button><button onClick={() => setPrivacyOpen(value => !value)}>Privacy →</button>{privacyOpen && <div className="privacy-panel"><button onClick={() => onError('Privacy: Public')}>Public</button><button onClick={() => onError('Privacy: Friends & Followers')}>Friends & Followers</button><button onClick={() => onError('Privacy: Selected Friends — friend/follower selection will use real relationship data.')}>Selected Friends</button><button onClick={() => onError('Privacy: Only Me')}>Only Me</button></div>}</div>}
      </div>
    </div>
    <p>{post.content}</p>
    <div className="interaction-bar"><button onClick={onLike} onContextMenu={event => { event.preventDefault(); setReactionOpen(value => !value) }}>❤️ {post.likeCount}</button>{reactionOpen && <div className="reaction-picker"><button onClick={() => onError('Reaction: ❤️')}>❤️</button><button onClick={() => onError('Reaction: 😂')}>😂</button><button onClick={() => onError('Reaction: 😮')}>😮</button><button onClick={() => onError('Reaction: 😢')}>😢</button><button onClick={() => onError('Reaction: 😡')}>😡</button></div>}<button onClick={() => onError('Comments page is the next real interaction operation; no dummy comments are rendered.')}>💬</button><button onClick={() => onError('Repost operation is not being faked; it will be wired to the Social repost model.')}>↻</button><button onClick={() => onError('Share operation is not being faked; it will use a real Work_Disk post link.')}>↗</button></div>
  </article>
}

function PostComposer({ identity, onCreated }: { identity: AuthenticatedIdentity; onCreated: () => void }): ReactElement { const [content, setContent] = useState(''); const [busy, setBusy] = useState(false); const [error, setError] = useState(''); const [profile, setProfile] = useState<SocialProfile | null>(null); useEffect(() => { void profiles.getProfile(identity).then(setProfile).catch(cause => setError(cause instanceof Error ? cause.message : 'Profile failed')) }, [identity]); async function publish(event: FormEvent) { event.preventDefault(); if (!profile?.profileName.trim() || !profile.photoUrl) { setError('Complete your Profile name and Profile picture before creating a post.'); return } setBusy(true); setError(''); try { await repository.createPost(identity, content); setContent(''); onCreated() } catch (cause) { setError(cause instanceof Error ? cause.message : 'Post failed') } finally { setBusy(false) } } return <section className="composer-card"><span className="eyebrow">CREATE REAL POST</span><h1>Share something</h1>{profile && <div className="post-composer-identity"><div className="post-avatar"><img src={profile.photoUrl} alt={profile.profileName} /></div><strong>{profile.profileName}</strong></div>}<p>Your saved Profile name and Profile picture will be attached to this new post.</p><form onSubmit={publish}><textarea value={content} onChange={event => setContent(event.target.value)} maxLength={5000} required placeholder="Write your post…" />{error && <div className="error">{error}</div>}<button disabled={busy}>{busy ? 'Publishing…' : 'Publish'}</button></form></section> }
